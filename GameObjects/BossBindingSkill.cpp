#include "pch.h"
#include "BossBindingSkill.h"
#include "SceneGame.h"
#include "ZombieBoss.h"
#include "TextGo.h"

BossBindingSkill::BossBindingSkill(const std::string& name)
{

}

BossBindingSkill::~BossBindingSkill()
{

}

void BossBindingSkill::Init()
{
	SpriteGo::Init();

	SetTexture(DT_STRING->Get("ZOMBIE_BOSS_BINDINGSKILL"));
	SetScale({ 0.2f , 0.2f });
	SetOrigin(Origins::MC);

	player = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetPlayer();

	binding = new TextGo("bindingText");
	binding->SetFont(DT_STRING->Get("FONT_1"));
	binding->SetString(L"스페이스바를 누르세요!!");
	binding->SetOrigin(Origins::MC);
	binding->SetCharacterSize(40);

	sortLayer = 22;

	SetPosition(player->GetPosition());

	bindingGauge = new ShapeGo<sf::RectangleShape>("bindingGauge");
	bindingGauge->SetPosition({player->GetPosition().x , 
		player->GetPosition().y + 100.f });
	bindingGauge->SetColor(sf::Color::Green);
	bindingGaugeMaxSize = { 300.f , 40.f };
	bindingGauge->SetSize(bindingGaugeMaxSize);
	bindingGauge->SetOrigin(Origins::MC);


	(SCENE_MGR.GetScene(SceneIds::SceneGame)->AddGo(bindingGauge, Scene::World));
	(SCENE_MGR.GetScene(SceneIds::SceneGame)->AddGo(binding, Scene::World));

	bindingGauge->SetActive(false);
	binding->SetActive(false);

	SetActive(false);
}

void BossBindingSkill::Release()
{
	SpriteGo::Release();
}

void BossBindingSkill::Reset()
{
	SpriteGo::Reset();
	SetPosition(player->GetPosition());

}

void BossBindingSkill::Update(float dt)
{
	SpriteGo::Update(dt);

	player->SetPosition(playerPos);

	if (bindingGauge->GetSize().x - speed * dt <= 0)
	{
		bindingGauge->SetSize({ 0.f , bindingGauge->GetSize().y });
	}
	else
	{
		bindingGauge->SetSize({ bindingGauge->GetSize().x - speed * dt,
			bindingGauge->GetSize().y });
	}

	if (isBinding && InputMgr::GetKeyUp(sf::Keyboard::Space))
	{
		if (bindingGauge->GetSize().x + addGauge > bindingGaugeMaxSize.x)
		{
			SetActive(false);
			bindingGauge->SetActive(false);
			binding->SetActive(false);
			isBinding = false;
		}

		bindingGauge->SetSize({ bindingGauge->GetSize().x + addGauge,
			bindingGauge->GetSize().y });
	}
}

void BossBindingSkill::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);

}

void BossBindingSkill::Draw(sf::RenderWindow & window)
{
	SpriteGo::Draw(window);
}

void BossBindingSkill::DebugUpdate(float dt)
{
	SpriteGo::DebugUpdate(dt);
}

void BossBindingSkill::DebugDraw(sf::RenderWindow & window)
{
	SpriteGo::DebugDraw(window);
}

void BossBindingSkill::BindingSkill()
{
	//std::cout << "BindingSkill!!" << std::endl; 테스트코드

	isBinding = true;
	zombieBoss = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetZomieBoss();
	bindingGauge->SetSize({ 0 , bindingGauge->GetSize().y });
	SetPosition(player->GetPosition());

	playerPos = player->GetPosition();

	bindingGauge->SetPosition({ playerPos.x , playerPos.y + 100.f });
	binding->SetPosition({ playerPos.x , playerPos.y - 100.f });

	SetActive(true);
	bindingGauge->SetActive(true);
	binding->SetActive(true);

	//zombieBoss->SetStatus(ZombieBoss::STATUS::MOVE);
}
