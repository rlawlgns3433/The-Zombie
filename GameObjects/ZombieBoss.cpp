#include "pch.h"
#include "ZombieBoss.h"
#include "SceneGame.h"
#include "EffectDamage.h"
#include "SpriteGo.h"
#include "BossRangeSkill.h"
#include "BossBindingSkill.h"

ZombieBoss* ZombieBoss::Create(Scene* sc)
{
	ZombieBoss* zombieBoss = new ZombieBoss(sc, "Zombie");

	zombieBoss->Init();
	zombieBoss->Reset();

	zombieBoss->bound.setRadius(zombieBoss->GetLocalBounds().width / 3);
	Utils::SetOrigin(zombieBoss->bound, Origins::MC);
	zombieBoss->scene->AddGo(zombieBoss);

	return zombieBoss;
}

ZombieBoss::ZombieBoss(const std::string& name)
	: SpriteGo(name)
{
	sortLayer = 11;
}

ZombieBoss::ZombieBoss(Scene* sc, const std::string& name)
	:SpriteGo(sc, name)
{
	sortLayer = 11;
}

void ZombieBoss::Init()
{
	SpriteGo::Init();

	currentStatus = STATUS::MOVE;

	SetScale({ 0.5f , 0.5f });

	SetTexture(DT_STRING->Get("ZOMBIE_BOSS"));
	SetOrigin(Origins::MC);

	bound.setOutlineColor(sf::Color::Magenta);
	bound.setOutlineThickness(1);
	bound.setFillColor(sf::Color(255, 255, 255, 0));
	rangeSkillDT = 0.3f;

	hpBar = new ShapeGo<sf::RectangleShape>("BossHpBar");
	hpBarBlack = new ShapeGo<sf::RectangleShape>("BossHpBarBlack");

	hpBar->SetColor(sf::Color::Red);
	hpBarBlack->SetColor(sf::Color::Black);
	hpBarSize = { 1920.f, 20.f };
	hpBar->SetSize(hpBarSize);
	hpBarBlack->SetSize(hpBarSize);
	hpBar->SetOrigin(Origins::TC);
	hpBarBlack->SetOrigin(Origins::TC);
	hpBar->SetPosition({ 1920 * 0.5f , 0.f });
	hpBarBlack->SetPosition({ 1920 * 0.5f , 0.f });

	bossBindingSkill = new BossBindingSkill("BossBindingSkill");
	bossBindingSkill->Init();

	(SCENE_MGR.GetScene(SceneIds::SceneGame)->AddGo(bossBindingSkill, Scene::World));
	(SCENE_MGR.GetScene(SceneIds::SceneGame)->AddGo(hpBarBlack, Scene::Ui));
	(SCENE_MGR.GetScene(SceneIds::SceneGame)->AddGo(hpBar , Scene::Ui));

	player = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetPlayer();

}

void ZombieBoss::Release()
{
	SpriteGo::Release();
}

void ZombieBoss::Reset()
{
	SpriteGo::Reset();
}

void ZombieBoss::Update(float dt)
{
	SpriteGo::Update(dt);

	atkTimer += dt;
	

	direction = player->GetPosition() - position;

	Utils::Normalize(direction);

	//충돌 검사
	Collision(dt);

	if (currentStatus == STATUS::MOVE && rangeSkillTimer > rangeSkillTime)
	{
		currentStatus = STATUS::RANGESKILL;
		rangeSkillTimer = 0.f;
	}
	else if (currentStatus == STATUS::MOVE && bidingSkillTimer > bidingSkillTime)
	{
		currentStatus = STATUS::BINDING_SKILL;
		bidingSkillTimer = 0.f;
	}

	switch (currentStatus)
	{
	case ZombieBoss::STATUS::MOVE:
		rangeSkillTimer += dt;
		bidingSkillTimer += dt;
		if (distanceToPlayer > GetBound().getRadius() + player->GetBound().getRadius())
		{
			Translate(direction * speed * dt);
			if (speed >= maxSpeed)
			{
				speed = 0.f;
				atkTimer = 0.f;
			}
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
		{
			currentStatus = STATUS::BINDING_SKILL;
		}

		break;
	case ZombieBoss::STATUS::RANGESKILL:
		rangeSkillDT += dt;
		if (rangeSkillCount >= rangeSkillCountMax)
		{
			currentStatus = STATUS::MOVE;
			rangeSkillDT = 0.3f;
			rangeSkillCount = 0;
			return;
		}
		else if (rangeSkillDT > rangeSkillDuration)
		{
			RangeSkill();
			break;
		}
		break;
	case ZombieBoss::STATUS::BINDING_SKILL:
		bossBindingSkill->BindingSkill();
		currentStatus = STATUS::MOVE;
		break;
	}

	if (!useRangeSkill.empty())
	{

	}

}

void ZombieBoss::FixedUpdate(float dt)
{
	distanceToPlayer = Utils::Distance(player->GetPosition(), position);

	SpriteGo::Update(dt);

	if (atkTimer >= atkInterval && distanceToPlayer <= GetBound().getRadius() + player->GetBound().getRadius())
	{
		player->OnDamage(atkDamage);
		atkTimer = 0.f;
	}

	switch (player->GetWeaponType())
	{
		case Player::TYPES::MAN:

			break;
		case Player::TYPES::FIREBAT:

			break;
		case Player::TYPES::READDEATH:

			break;
	}
}

void ZombieBoss::Draw(sf::RenderWindow & window)
{
	SpriteGo::Draw(window);

}

void ZombieBoss::SetHp(int hp, int max)
{
	float value = max > 0 ? (float)hp / max : 0;
	hpBar->SetSize({ hpBarSize.x * value, hpBarSize.y });
}

void ZombieBoss::DebugUpdate(float dt)
{
	SpriteGo::DebugUpdate(dt);

	bound.setPosition(position);
}

void ZombieBoss::DebugDraw(sf::RenderWindow & window)
{
	SpriteGo::DebugDraw(window);
}

void ZombieBoss::RangeSkill()
{
	// useRangeSkill , unuseRangeSkill 수정필요
	BossRangeSkill* bossRangleSkill = nullptr;

	if (unuseRangeSkill.empty())
	{
		bossRangleSkill = BossRangeSkill::Create();
	}
	else
	{
		bossRangleSkill = unuseRangeSkill.front();
		unuseRangeSkill.pop_front();
		bossRangleSkill->Init();
		bossRangleSkill->Reset();
	}

	useRangeSkill.push_back(bossRangleSkill);
	SCENE_MGR.GetCurrentScene()->AddGo(bossRangleSkill);

	rangeSkillCount++;
	rangeSkillDT = 0.f;

	//SpriteGo* rangeSkill = new SpriteGo();

	//useRangeSkill.push_back(rangeSkill);
	
	//SCENE_MGR.GetCurrentScene()->AddGo(rangeSkill);
}

void ZombieBoss::BindingSkill()
{

}

void ZombieBoss::SetStatus(STATUS stat)
{
	currentStatus = stat;
}

bool ZombieBoss::Damaged(int damage)
{
	int preHp = hp;
	hp = std::max(hp - damage, 0);
	SetHp(hp, maxHp);
	//hp -= damage;
	if (scene != nullptr)
	{
	EffectDamage::Create(scene, position, damage);
	}
	if (hp <= 0 && !isDead)
	{
		hp = 0;
		OnDie();
	}
	return isDead;
}

void ZombieBoss::Collision(float dt)
{
	//윈도우
	sf::Vector2f tempPos = position;
	std::pair<sf::Vector2f, sf::Vector2f> boundary = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoundary();

	if (tempPos.x < boundary.first.x)
		Utils::ElasticCollision(tempPos.x, boundary.first.x, 0.f);
	if (tempPos.x > boundary.second.x)
		Utils::ElasticCollision(tempPos.x, boundary.second.x, 0.f);
	if (tempPos.y < boundary.first.y)
		Utils::ElasticCollision(tempPos.y, boundary.first.y, 0.f);
	if (tempPos.y > boundary.second.y)
		Utils::ElasticCollision(tempPos.y, boundary.second.y, 0.f);

	SetPosition(tempPos);
	//rotation = Utils::Angle(player->GetPosition() - GetPosition());
	//SetRotation(rotation);
}

void ZombieBoss::OnDie()
{
	isDead = true;
	SCENE_MGR.GetCurrentScene()->DeleteGo(this);
	SCENE_MGR.GetCurrentScene()->DeleteGo(hpBar);
	SCENE_MGR.GetCurrentScene()->DeleteGo(hpBarBlack);
	dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->SetZombieBossDead(true);
}
