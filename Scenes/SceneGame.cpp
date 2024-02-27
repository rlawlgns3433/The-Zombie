#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ItemSpawner.h"
#include "Bullet.h"
#include "Crosshair.h"
#include "Item.h"
#include "DebugString.h"
#include "UIHUD.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id), player(nullptr), hud(nullptr), tileMap(nullptr)
{
}

void SceneGame::Init()
{
	Release();

	//UI
	crosshair = dynamic_cast<Crosshair*>(AddGo(new Crosshair(), Scene::Ui));

	hud = dynamic_cast<UIHUD*>(AddGo(new UIHUD(), Scene::Ui));

	//AddGo(new DebugString(), Scene::Ui);

	//���
	tileMap = dynamic_cast<TileMap*>(AddGo(new TileMap("Background")));

	//���� ������
	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ItemSpawner());
	for (auto s : spawners)
	{
		if (s->name == "ItemSpawner")
		{
			s->SetPosition({ FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y * 0.5f });
		}
		else if (s->name == "ZombieSpawner")
		{
			s->SetPosition({ Utils::RandomRange(boundary.first.x,boundary.second.x),Utils::RandomRange(boundary.first.y,boundary.second.y) });
		}
		AddGo(s);
	}

	//�÷��̾�
	player = new Player("Player");
	AddGo(player);

	Scene::Init();

	//���̺�
	wave = 0;
	zombieCount = 1;

	hud->SetScore(score);
	hud->SetHiScore(hiScore);
	hud->SetAmmo(0, 0);
	hud->SetWave(wave);
	hud->SetZombieCount(zombieCount);
}

void SceneGame::Release()
{
	Scene::Release();
	for (auto ptr : zombieObjects)
	{
		ptr = nullptr;
	}
	zombieObjects.clear();
	for (auto ptr : spawners)
	{
		ptr = nullptr;
	}
	spawners.clear();
	for (auto ptr : bullets)
	{
		ptr = nullptr;
	}
	bullets.clear();
	player = nullptr;
	score = 0;
	wave = 0;
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);
	Scene::Enter();

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f,0.f });
	uiView.setSize(windowSize);

	//tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	tileMap->SetPosition(centerPos);
	boundary = tileMap->GetBoundary();
	tileMap->SetOrigin(Origins::MC);
	//tileMap->SetRotation(45);
	//tileMap->SetScale({ 2.f,2.f });
	tileMap->UpdateTransform();

	player->SetPosition(GetBoundaryCenter());
	worldView.setCenter(player->GetPosition());

}

void SceneGame::Exit()
{
	Scene::Exit();
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
	doReset = true;
}

void SceneGame::Update(float dt)
{
	switch (status)
	{
		/////////////////////////////////////////////////////////////////////////////PLAY
	case SceneGame::Status::PLAY:
		Scene::Update(dt);
		//�߰�
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			for (auto s : spawners)
			{
				if (s->name == "ZombieSpawner")
					s->Spawn(1);
			}
		}
		//���� ����
		if (InputMgr::GetKeyDown(sf::Keyboard::Delete))
		{
			while (zombieObjects.size() > 0)
			{
				Zombie* temp = zombieObjects.front();
				RemoveGo(temp);
				zombieObjects.pop_front();
				delete temp;
			}
		}
		//�ϳ��� �����ϰ� ����
		if (InputMgr::GetKey(sf::Keyboard::BackSpace))
		{
			size_t siz = zombieObjects.size();
			if (siz != 0)
			{
				int t = rand() % siz;
				auto it = zombieObjects.begin();
				for (int i = 0; i < t; i++)
				{
					it++;
				}
				RemoveGo(*it);
				Zombie* z = *it;
				zombieObjects.remove(*it);
				delete z;
			}
		}
		zombieObjects.sort();

		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			status = Status::PAUSE;
		}

		break;
		////////////////////////////////////////////////////////////////////////////PAUSE
	case SceneGame::Status::PAUSE:

		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			status = Status::PLAY;
		}
		crosshair->Update(dt);

		break;
	default:
		break;
	}
}

void SceneGame::LateUpdate(float dt)
{
	switch (status)
	{
	case SceneGame::Status::PLAY:
		Scene::LateUpdate(dt);

		//������Ʈ ���� (delete)
		while (deleteDeque.size() > 0)
		{
			//�ʿ��� ������ �̸� �����´�.
			GameObject* temp = deleteDeque.front();
			int tag = temp->GetTag();

			//���� ����
			RemoveGo(temp);
			deleteDeque.pop_front();
			if (tag == 0)
				zombieObjects.remove(dynamic_cast<Zombie*>(temp));
			else if (tag == 1)
				bullets.remove(dynamic_cast<Bullet*>(temp));
			delete temp;
		}
		if (doReset)
		{
			doReset = false;
			Release();
			Init();
			Enter();
		}
		break;
	case SceneGame::Status::PAUSE:
		crosshair->LateUpdate(dt);
		break;
	default:
		break;
	}

}

void SceneGame::FixedUpdate(float dt)
{
	switch (status)
	{
	case SceneGame::Status::PLAY:
		Scene::FixedUpdate(dt);
		BulletCollision(dt);
		if (zombieCount <= 0)
			ChangeWave(++wave);
		break;
	case SceneGame::Status::PAUSE:
		crosshair->FixedUpdate(dt);
		break;
	default:
		break;
	}


	sf::Vector2f viewSpeed = player->GetPosition() - worldView.getCenter();
	worldView.move(viewSpeed * dt * 2.f);
	//worldView.setCenter(Utils::Lerp(worldView.getCenter(), player->GetPosition(), dt));
	if (Utils::Distance(player->GetPosition(), worldView.getCenter()) <= 1.f && InputMgr::GetAxis(Axis::Horizontal) == 0.f && InputMgr::GetAxis(Axis::Vertical) == 0.f)
		worldView.setCenter(player->GetPosition());
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::AddScore(int s)
{
	score += s;
	hud->SetScore(score);
	hud->SetHiScore(hiScore = std::max(score, hiScore));
}



void SceneGame::ChangeWave(int w)
{
	this->wave = w;

	ReleaseWave();
	InitWave();

	hud->SetWave(wave);
	hud->SetZombieCount(zombieCount);

	status = Status::PLAY;
}

void SceneGame::ReleaseWave()
{

	deleteDeque.clear();
	auto it = gameObjects.begin();
	while (it != gameObjects.end())
	{
		if ((*it)->name == "Player" || (*it)->name == "Background")
		{
			it++;
		}
		else
		{
			delete* it;
			it = gameObjects.erase(it);
		}
	}

	for (auto ptr : zombieObjects)
	{
		ptr = nullptr;
	}
	zombieObjects.clear();
	for (auto ptr : spawners)
	{
		ptr = nullptr;
	}
	spawners.clear();
	for (auto ptr : bullets)
	{
		ptr = nullptr;
	}
	bullets.clear();
}

void SceneGame::InitWave()
{
	switch (wave)
	{
	case 0:
		break;
	case 1:
		tileMap->Set({ (int)20,(int)100 }, { 50.f,50.f });
		//tileMap->UpdateTransform();
		zombieCount = 1000000;
		break;
	default:
		break;
	}



	tileMap->SetOrigin(Origins::MC);
	tileMap->UpdateTransform();
	boundary = tileMap->GetBoundary();
	player->SetPosition(GetBoundaryCenter());

	spawners.push_back(new ItemSpawner());
	spawners.push_back(new ItemSpawner());
	spawners.push_back(new ItemSpawner());
	spawners.push_back(new ItemSpawner());
	spawners.push_back(new ItemSpawner());
	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ZombieSpawner());
	for (auto s : spawners)
	{
		s->SetPosition({ Utils::RandomRange(boundary.first.x,boundary.second.x),Utils::RandomRange(boundary.first.y,boundary.second.y) });
		AddGo(s);
		s->Init();
		s->Reset();
	}
}




void SceneGame::BulletCollision(float dt)
{
	for (auto zombie : zombieObjects)
	{
		if (zombie->isDead)
			continue;
		for (auto bullet : bullets)
		{
			if (!zombie->isDead && !bullet->isHit && Utils::IsCollideWithLineSegment(zombie->GetPosition(), bullet->GetPosition(), bullet->prePos, zombie->GetGlobalBounds().width / 3.f))
			{
				bullet->Hit();
				if (zombie->Damaged(bullet->damage))
				{
					AddScore(10);
					hud->SetZombieCount(--zombieCount);
				}
				zombie->SetPosition(zombie->GetPosition() + zombie->GetDirection() * -1.f * 5.f);
			}
		}
	}
}

sf::Vector2f SceneGame::GetBoundaryCenter()
{
	return sf::Vector2f(boundary.first.x + (boundary.second.x - boundary.first.x) * 0.5, boundary.first.y+(boundary.second.y - boundary.first.y)*0.5);
}

//sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f& point)
//{
//	sf::FloatRect rect = tileMap->GetGlobalBounds();
//	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);
//
//	return Utils::Clamp();
//}
