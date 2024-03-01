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
#include "WaveTable.h"
#include "EffectCenterText.h"
#include <SceneScore.h>


SceneGame::SceneGame(SceneIds id)
	:Scene(id), player(nullptr), hud(nullptr), tileMap(nullptr), uiLevel(nullptr)
{
	CheatExp();
	CheatHp();
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
	tileMap->SetOrigin(Origins::MC);
	tileMap->UpdateTransform();
	//플레이어
	player = new Player("Player");
	AddGo(player);

	Scene::Init();

	//웨이브
	ChangeWave(1);

	hud->SetScore(score);
	hud->SetHiScore(GetHighScore());
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
	ChangeWave(1);

	player->SetPosition(GetBoundaryCenter());
	worldView.setCenter(player->GetPosition());

	playTimer = 0.f;

	//Debug
	debugZombieCount = UI_DEBUG.AddText(new sf::Text);
}

void SceneGame::Exit()
{
	Scene::Exit();
	Init();
	FRAMEWORK.GetMouse()->isPlaying = false;
}

void SceneGame::Update(float dt)
{

	switch (status)
	{
		////////////////////////////////////////////////////////////////////////// PLAY_UPDATE
	case SceneGame::Status::PLAY:
		Scene::Update(dt);
		playTimer += dt;
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
		if (isWin)
		{
			WinAnimation(dt);
		}

		break;
		////////////////////////////////////////////////////////////////////////// DIE_UPDATE
	case SceneGame::Status::DIE:

		if (InputMgr::GetKeyUp(sf::Keyboard::Escape) || InputMgr::GetKeyUp(sf::Keyboard::Space) || InputMgr::GetKeyUp(sf::Keyboard::Enter))
		{
			//SaveHighScore(); //TODO 옮겨라 - CHECK SceneScore에서 저장할 예정
			hud->SetGameOver(false);
			dynamic_cast<SceneScore*>(SCENE_MGR.GetScene(SceneIds::SceneScore))->OnWriteMode(score, playTimer);
			SCENE_MGR.ChangeScene(SceneIds::SceneScore);
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

void SceneGame::WinAnimation(float dt)
{
	dynamic_cast<SceneScore*>(SCENE_MGR.GetScene(SceneIds::SceneScore))->OnWriteMode(score, playTimer);
	SCENE_MGR.ChangeScene(SceneIds::SceneScore);
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
		if (!isWin && zombieCount <= 0)
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


	if (InputMgr::GetKeyDown(sf::Keyboard::Slash))
	{
		InputMgr::StopComboRecord();
		InputMgr::ClearCombo();
		InputMgr::ComboRecord(10.f);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Period))
	{

		if (InputMgr::IsExllentCombo(cheatExp))
		{
			player->AddExp(10000);
		}
		if (InputMgr::IsExllentCombo(cheatHp))
		{
			player->SetInvincibility();
		}
		InputMgr::StopComboRecord();
		InputMgr::ClearCombo();
	}
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
}

void SceneGame::ReleaseWave()
{

	for (auto sPtr : spawners)
	{
		gameObjects.remove(sPtr);
		auto dIt = deleteDeque.begin();
		while (dIt != deleteDeque.end())
		{
			if (*dIt == sPtr)
			{
				dIt = deleteDeque.erase(dIt);
			}
			else
			{
				dIt++;
			}
		}
		delete sPtr;
	}
	spawners.clear();
}

void SceneGame::InitWave()
{
	const DATA_WAVE& data = DT_WAVE->Get(wave);

	if (wave == DT_WAVE->GetLastWave())
	{
		isWin = true;
		zombieCount = 0;
	}
	else
	{
		tileMap->Set({ data.tileX,data.tileY }, { 50.f, 50.f });
		zombieCount = data.zombieCount;
		for (int i = 0; i < data.itemAmount; i++)
		{
			ItemSpawner* is = new ItemSpawner(this);
			is->Init();
			is->Reset();
			spawners.push_back(is);
		}
		for (int i = 0; i < data.zombieAmount; i++)
		{
			ZombieSpawner* zs = new ZombieSpawner(this);
			zs->Init();
			zs->Reset();
			for (int z0 = 0; z0 < data.zombie0W; z0++) { zs->AddType(Zombie::Types::Chaser); }
			for (int z1 = 0; z1 < data.zombie1W; z1++) { zs->AddType(Zombie::Types::Bloater); }
			for (int z2 = 0; z2 < data.zombie2W; z2++) { zs->AddType(Zombie::Types::Crawler); }
			spawners.push_back(zs);
		}


		tileMap->SetOrigin(Origins::MC);
		tileMap->UpdateTransform();
		boundary = tileMap->GetBoundary();
		srand(time(NULL));
		for (auto s : spawners)
		{
			s->SetPosition(sf::Vector2f(Utils::RandomRange(boundary.first.x, boundary.second.x), Utils::RandomRange(boundary.first.y, boundary.second.y)));
			AddGo(s);
		}
		EffectCenterText::Create(this,data.descriptionId);
	}
}

void SceneGame::SaveHighScore()
{
	std::ifstream file("highScore.txt");

	if (!file.is_open()) {
		std::cerr << "파일을 열 수 없습니다." << std::endl;
		return;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	std::vector<std::string> lines;
	std::string line;

	std::ofstream input;
	input.open("highScore.txt", std::ios::app);
	if (input.is_open())
	{
		input << score << '\n' << playTimer;
	}

	input.close();
}

int SceneGame::GetHighScore()
{
	std::ifstream output;
	output.open("highScore.txt");

	if (output.is_open())
	{
		output >> hiScore;
	}
	output.close();

	return hiScore;
}

void SceneGame::BulletCollision(float dt)
{

	for (auto bullet : bullets)
	{
		for (auto zombie : zombieObjects)
		{
			if (!zombie->isDead && !bullet->isHit && bullet->CheckCollision(zombie))
			{
				bullet->Hit();
				if (zombie->Damaged(bullet->GetDamage()))
				{
					AddScore(1000);
					hud->SetZombieCount(--zombieCount);
				}
				zombie->SetPosition(zombie->GetPosition() + zombie->GetDirection() * -1.f * 5.f);
			}
		}
		bullet->EndOfCheckZombie();
	}
}

sf::Vector2f SceneGame::GetBoundaryCenter()
{
	return sf::Vector2f(boundary.first.x + (boundary.second.x - boundary.first.x) * 0.5, boundary.first.y + (boundary.second.y - boundary.first.y) * 0.5);
}



//치트 콤보 - TODO 데이터테이블화..?
void SceneGame::CheatExp()
{
	cheatExp.push_back({ sf::Keyboard::S,InputMgr::KEY_STATE::DOWN });
	cheatExp.push_back({ sf::Keyboard::H,InputMgr::KEY_STATE::DOWN });
	cheatExp.push_back({ sf::Keyboard::O,InputMgr::KEY_STATE::DOWN });
	cheatExp.push_back({ sf::Keyboard::W,InputMgr::KEY_STATE::DOWN });
	cheatExp.push_back({ sf::Keyboard::M,InputMgr::KEY_STATE::DOWN });
	cheatExp.push_back({ sf::Keyboard::E,InputMgr::KEY_STATE::DOWN });
	cheatExp.push_back({ sf::Keyboard::T,InputMgr::KEY_STATE::DOWN });
	cheatExp.push_back({ sf::Keyboard::H,InputMgr::KEY_STATE::DOWN });
	cheatExp.push_back({ sf::Keyboard::E,InputMgr::KEY_STATE::DOWN });
	cheatExp.push_back({ sf::Keyboard::M,InputMgr::KEY_STATE::DOWN });
	cheatExp.push_back({ sf::Keyboard::O,InputMgr::KEY_STATE::DOWN });
	cheatExp.push_back({ sf::Keyboard::N,InputMgr::KEY_STATE::DOWN });
	cheatExp.push_back({ sf::Keyboard::E,InputMgr::KEY_STATE::DOWN });
	cheatExp.push_back({ sf::Keyboard::Y,InputMgr::KEY_STATE::DOWN });
}
void SceneGame::CheatHp()
{
	cheatHp.push_back({ sf::Keyboard::H,InputMgr::KEY_STATE::DOWN });
	cheatHp.push_back({ sf::Keyboard::P,InputMgr::KEY_STATE::DOWN });
}