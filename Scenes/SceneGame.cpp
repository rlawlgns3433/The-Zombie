#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ItemSpawner.h"
#include "Bullet.h"
#include "Crosshair.h"
#include "UIHUD.h"
#include "UIDebug.h"
#include "Flame.h"
#include "Projectile.h"
#include "UILevelUp.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id), player(nullptr), hud(nullptr), tileMap(nullptr)
{
}

void SceneGame::Init()
{
	Release();

	//UI
	//crosshair = dynamic_cast<Crosshair*>(AddGo(new Crosshair(), Scene::Ui));
	hud = dynamic_cast<UIHUD*>(AddGo(new UIHUD(), Scene::Ui));
	uiLevel = dynamic_cast<UILevelUp*>(AddGo(new UILevelUp("uiLevel"), Scene::Ui));
	//배경
	tileMap = dynamic_cast<TileMap*>(AddGo(new TileMap("Background")));
	//좀비 스포너
	spawners.push_back(new ZombieSpawner(this));
	spawners.push_back(new ItemSpawner(this));
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

	UI_DEBUG.RemoveText(debugZombieCount);
	if (debugZombieCount != nullptr)
	{
		delete debugZombieCount;
		debugZombieCount = nullptr;
	}
}

void SceneGame::Reset()
{
	Scene::Reset();

}

void SceneGame::Enter()
{
	Scene::Enter();
	Reset();
	SetStatus(Status::PLAY);

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f,0.f });
	uiView.setSize(windowSize);

	tileMap->SetPosition(centerPos);
	boundary = tileMap->GetBoundary();
	tileMap->SetOrigin(Origins::MC);
	tileMap->UpdateTransform();
	player->SetPosition(GetBoundaryCenter());
	worldView.setCenter(player->GetPosition());

	//Debug
	debugZombieCount = UI_DEBUG.AddText(new sf::Text);
}

void SceneGame::Exit()
{
	Scene::Exit();
	Init();

}

void SceneGame::Update(float dt)
{
	switch (status)
	{
		////////////////////////////////////////////////////////////////////////// PLAY_UPDATE
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

		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			SetStatus(Status::PAUSE);
		}

		break;
		////////////////////////////////////////////////////////////////////////// DIE_UPDATE
	case SceneGame::Status::DIE:
		if (InputMgr::GetKeyUp(sf::Keyboard::Escape)|| InputMgr::GetKeyUp(sf::Keyboard::Space)|| InputMgr::GetKeyUp(sf::Keyboard::Enter))
		{
			hud->SetGameOver(false);
			SCENE_MGR.ChangeScene(SceneIds::SceneTitle);
		}
		for (auto obj : uiObjects)
		{
			if (obj->GetActive())
			{
				obj->LateUpdate(dt);
			}
		}
		break;
		////////////////////////////////////////////////////////////////////////// PAUSE_UPDATE
	case SceneGame::Status::PAUSE:

		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			hud->SetPause(false);
			SetStatus(Status::PLAY);
		}

		for (auto obj : uiObjects)
		{
			if (obj->GetActive())
			{
				obj->LateUpdate(dt);
			}
		}
		break;
		////////////////////////////////////////////////////////////////////////// LEVELUP_UPDATE
	case SceneGame::Status::LEVELUP:

		for (auto obj : uiObjects)
		{
			if (obj->GetActive())
			{
				obj->Update(dt);
			}
		}
		break;

	default:
		break;
	}
}

void SceneGame::LateUpdate(float dt)
{
	while (!deleteDeque.empty())
	{
		//�ʿ��� ������ �̸� �����´�.
		GameObject* temp = deleteDeque.front();
		int tag = temp->GetTag();

		//���� ����
		RemoveGo(temp);
		if (tag == 0)
			zombieObjects.remove(dynamic_cast<Zombie*>(temp));
		else if (tag == 1)
			bullets.remove(dynamic_cast<Projectile*>(temp));
		deleteDeque.pop_front();
		delete temp;	// CHECK 문제 소지 있음 >> 위치 변경으로 테스트 중
	}

	switch (status)
	{
		////////////////////////////////////////////////////////////////////////// PLAY_LATE
	case SceneGame::Status::PLAY:
		Scene::LateUpdate(dt);

		//������Ʈ ���� (delete)

		break;
		////////////////////////////////////////////////////////////////////////// DIE_LATE
	case SceneGame::Status::DIE:
		for (auto obj : uiObjects)
		{
			if (obj->GetActive())
			{
				obj->LateUpdate(dt);
			}
		}
		break;
		////////////////////////////////////////////////////////////////////////// PAUSE_LATE
	case SceneGame::Status::PAUSE:
		for (auto obj : uiObjects)
		{
			if (obj->GetActive())
			{
				obj->LateUpdate(dt);
			}
		}
		break;
		////////////////////////////////////////////////////////////////////////// LEVELUP_LATE
	case SceneGame::Status::LEVELUP:

		for (auto obj : uiObjects)
		{
			if (obj->GetActive())
			{
				obj->LateUpdate(dt);
			}
		}
		break;
	default:
		break;
	}

}

void SceneGame::FixedUpdate(float dt)
{
	switch (status)
	{
		////////////////////////////////////////////////////////////////////////// PLAY_FIXED
	case SceneGame::Status::PLAY:
		Scene::FixedUpdate(dt);
		zombieObjects.sort();
		BulletCollision(dt);
		if (zombieCount <= 0)
			ChangeWave(++wave);
		break;
		////////////////////////////////////////////////////////////////////////// DIE_FIXED
	case SceneGame::Status::DIE:
		for (auto obj : uiObjects)
		{
			if (obj->GetActive())
			{
				obj->FixedUpdate(dt);
			}
		}
		break;
		////////////////////////////////////////////////////////////////////////// PAUSE_FIXED
	case SceneGame::Status::PAUSE:
		for (auto obj : uiObjects)
		{
			if (obj->GetActive())
			{
				obj->FixedUpdate(dt);
			}
		}
		break;
		////////////////////////////////////////////////////////////////////////// LEVELUP_FIXED
	case SceneGame::Status::LEVELUP:
		for (auto obj : uiObjects)
		{
			if (obj->GetActive())
			{
				obj->FixedUpdate(dt);
			}
		}
		if (!uiLevel->GetActive())
		{
			SetStatus(Status::PLAY);
			player->AddStat(uiLevel->PlayerLevelUp());
		}
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

void SceneGame::DebugUpdate(float dt)
{
	Scene::DebugUpdate(dt);
	debugZombieCount->setString("zombies: " + std::to_string(zombieObjects.size()));
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::SetStatus(Status st)
{

	switch (st)
	{
	case SceneGame::Status::PLAY:
		FRAMEWORK.GetMouse()->isPlaying = true;
		break;
	case SceneGame::Status::PAUSE:
		FRAMEWORK.GetMouse()->isPlaying = false;
		hud->SetPause(true);
		break;
	case SceneGame::Status::DIE:
		FRAMEWORK.GetMouse()->isPlaying = false;
		hud->SetGameOver(true);
		break;
	case SceneGame::Status::LEVELUP:
		FRAMEWORK.GetMouse()->isPlaying = false;
		uiLevel->LevelUp();
		break;
	default:
		break;
	}

	status = st;
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

	SetStatus(Status::PLAY);
}

void SceneGame::ReleaseWave()
{

	deleteDeque.clear();
	auto it = gameObjects.begin();
	while (it != gameObjects.end())
	{
		if ((*it)->name == "Player" || (*it)->name == "Background" || (*it)->name == "Gun")
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
		tileMap->Set({ (int)40,(int)40 }, { 50.f,50.f });
		zombieCount = 1000000;
		break;
	default:
		break;
	}



	tileMap->SetOrigin(Origins::MC);
	tileMap->UpdateTransform();
	boundary = tileMap->GetBoundary();
	player->SetPosition(GetBoundaryCenter());

	spawners.push_back(new ItemSpawner(this));
	spawners.push_back(new ItemSpawner(this));
	spawners.push_back(new ItemSpawner(this));
	spawners.push_back(new ItemSpawner(this));
	spawners.push_back(new ItemSpawner(this));
	spawners.push_back(new ZombieSpawner(this));
	spawners.push_back(new ZombieSpawner(this));
	spawners.push_back(new ZombieSpawner(this));
	spawners.push_back(new ZombieSpawner(this));
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
			if (!zombie->isDead && !bullet->isHit && bullet->CheckCollision(zombie))
			{
				bullet->Hit();
				if (zombie->Damaged(bullet->GetDamage()))
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
	return sf::Vector2f(boundary.first.x + (boundary.second.x - boundary.first.x) * 0.5, boundary.first.y + (boundary.second.y - boundary.first.y) * 0.5);
}

//sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f& point)
//{
//	sf::FloatRect rect = tileMap->GetGlobalBounds();
//	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);
//
//	return Utils::Clamp();
//}
