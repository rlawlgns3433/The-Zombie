#include "pch.h"
#include "BossRangeSkill.h"
#include "ZombieBoss.h"
#include "SceneGame.h"

BossRangeSkill* BossRangeSkill::Create()
{
	BossRangeSkill* bossRangeSkill = new BossRangeSkill();
	bossRangeSkill->Init();
	bossRangeSkill->Reset();

	return bossRangeSkill;
}

BossRangeSkill::BossRangeSkill(const std::string& name)
	: SpriteGo(name)
{
	sortLayer = 13;
}

void BossRangeSkill::Init()
{
	SpriteGo::Init();

	SetTexture(DT_STRING->Get("ZOMBIE_BOSS_RANGLESKILL"));
	SetScale({ 0.2f , 0.2f });
	SetOrigin(Origins::MC);
	hit = false;

	player = dynamic_cast<SceneGame*>
		(SCENE_MGR.GetCurrentScene())->GetPlayer();
	zombieBoss = dynamic_cast<SceneGame*>
		(SCENE_MGR.GetCurrentScene())->GetZomieBoss();

	direction = player->GetPosition() - zombieBoss->GetPosition();

	SetPosition(zombieBoss->GetPosition());

	SetRotation(Utils::Angle(direction) + 235);
}

void BossRangeSkill::Release()
{
	SpriteGo::Release();
}

void BossRangeSkill::Reset()
{
	SpriteGo::Reset();
}

void BossRangeSkill::Update(float dt)
{
	SpriteGo::Update(dt);

	
}

void BossRangeSkill::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);

	dtime += dt;

	Translate(direction * speed * dt);
	
	// **********************수정해야함******************
	// while 문 돌아야함
	auto it = zombieBoss->GetUseRangeSkill().begin();

	while (it != zombieBoss->GetUseRangeSkill().end())
	{
		if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
		{
			std::cout << "플레이어 맞음" << std::endl;
			hit = true;
			zombieBoss->GetUnUseRangeSkill().push_back(this);
			it = zombieBoss->GetUseRangeSkill().erase(it);
		}
		else
		{
			it++;
		}
	}


	// **********************수정해야함******************
	if (dtime > unUseListTime && !hit)
	{
		//zombieBoss->GetUseRangeSkill().erase(it);
	}

}

void BossRangeSkill::Draw(sf::RenderWindow & window)
{
	SpriteGo::Draw(window);
}

void BossRangeSkill::DebugUpdate(float dt)
{
	SpriteGo::DebugUpdate(dt);
}

void BossRangeSkill::DebugDraw(sf::RenderWindow & window)
{
	SpriteGo::DebugDraw(window);
}
