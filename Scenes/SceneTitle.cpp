#include "pch.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "rapidcsv.h"
#include "ZombieTable.h"
#include "TextGo.h"
#include "UICharacterSelect.h"

SceneTitle::SceneTitle(SceneIds id)
	:Scene(id)
{
	SpriteGo* bg = new SpriteGo("bg");
	bg->SetTexture("graphics/titlebackground.png");
	AddGo(bg, Scene::Ui);
}

void SceneTitle::Init()
{
	Scene::Init();

	//*************************텍스트*************************
	sf::Font& font = RES_MGR_FONT.Get("fonts/BMHANNAPro.ttf");

	texts.insert({ "Title", new TextGo("Title") });
	texts.insert({ "Start", new TextGo("Start") });

	texts["Title"]->SetFont(font);
	texts["Start"]->SetFont(font);

	texts["Title"]->sortLayer = 10;
	texts["Start"]->sortLayer = 10;

	texts["Title"]->SetString(L"좀비 서바이벌");
	texts["Start"]->SetString(L"시작하려면 Enter를 눌러주세요");

	texts["Title"]->SetCharacterSize(150);
	texts["Start"]->SetCharacterSize(40);

	texts["Title"]->SetColor(sf::Color::Red);
	texts["Start"]->SetColor(sf::Color::White);

	texts["Title"]->SetOutLine(10.f, sf::Color::Black);

	texts["Title"]->SetOrigin(Origins::MC);
	texts["Start"]->SetOrigin(Origins::MC);

	texts["Title"]->SetPosition( { FRAMEWORK.GetWindowSize().x * 0.5f,
		  FRAMEWORK.GetWindowSize().y * 0.3f});

	texts["Start"]->SetPosition( { FRAMEWORK.GetWindowSize().x * 0.5f ,
		FRAMEWORK.GetWindowSize().y * 0.8f});

	AddGo(texts["Title"] , Scene::Ui);
	AddGo(texts["Start"] , Scene::Ui);

	// 캐릭터 선택 클래스 

	uiCharacterSelect = new UICharacterSelect("UICharacterSelect");

	uiCharacterSelect->sortLayer = 11;

	AddGo(uiCharacterSelect, Scene::Ui);
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::SceneGame);
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

	if (scale.x <= 1.0f)
	{
		isMius = false;
	}
	else if (scale.x >= 1.2f)
	{
		isMius = true;
	}

	if (isMius)
	{
		scale.x -= speed * dt;
		scale.y -= speed * dt;
	}
	else if (!isMius)
	{
		scale.x += speed * dt;
		scale.y += speed * dt;
	}

	texts["Start"]->SetScale({ scale });

}

void SceneTitle::Enter()
{
	Scene::Enter();
	SOUND_MGR.PlayBGM("sound/SellBuyMusic1.wav");

	//std::cout << DT_ZOMBIE->Get(Zombie::Types::Bloater).atkInterval << std::endl;
}
