#include "pch.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "rapidcsv.h"
#include "ZombieTable.h"

SceneTitle::SceneTitle(SceneIds id)
	:Scene(id)
{
	SpriteGo* bg = new SpriteGo("bg");
	bg->SetTexture("graphics/background.png");
	AddGo(bg, Scene::Ui);
}

void SceneTitle::Init()
{
	Scene::Init();

	uiLevelUp = new UILevelUp("UILevelUp");
	uiLevelUp->Init();

	AddGo(uiLevelUp, Scene::Ui);
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::SceneGame);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		if (uiLevelUp->GetActive())
		{
			uiLevelUp->SetActive(false);
		}
		else
		{
			uiLevelUp->SetActive(true);
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::S))
	{
		DT_STRING->Load(Languages::English);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		DT_STRING->Load(Languages::Korean);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		std::cout << DT_STRING->Get("a") << std::endl;
	}
}

void SceneTitle::Enter()
{
	Scene::Enter();
	SOUND_MGR.PlayBGM("sound/SellBuyMusic1.wav");

	std::cout << DT_ZOMBIE->Get(Zombie::Types::Bloater).atkInterval << std::endl;

}
