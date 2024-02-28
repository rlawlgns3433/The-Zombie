#include "pch.h"
#include "Zombie.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "EffectBlood.h"
#include "ZombieTable.h"
#include "Item.h"

Zombie::Zombie(const std::string& name)
	: SpriteGo(name)
{
	tag = 0;
	sortLayer = 10;
}

Zombie::Zombie(Scene* sc, const std::string& name)
	:SpriteGo(sc, name)
{
	tag = 0;
	sortLayer = 10;
}

Zombie* Zombie::Create(Types zombieType,Scene* sc)
{
	Zombie* zombie = new Zombie(sc,"Zombie");
	zombie->type = zombieType;


	const DataZombie& data = DT_ZOMBIE->Get(zombieType);
	zombie->textureId = data.textureId;
	zombie->hp = zombie->maxHp = data.maxHp;
	zombie->speed = zombie->maxSpeed = data.maxSpeed;
	zombie->atkDamage = data.atkDamage;
	zombie->atkTimer = zombie->atkInterval = data.atkInterval;

	zombie->Init();
	zombie->Reset();
	zombie->player = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetPlayer();

	dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->zombieObjects.push_back(zombie);
	zombie->bound.setRadius(zombie->GetLocalBounds().width / 3);
	Utils::SetOrigin(zombie->bound, Origins::MC);

	return zombie;
}

void Zombie::Init()
{
	SpriteGo::Init();

	SetTexture(textureId);
	SetOrigin(Origins::MC);


	bound.setOutlineColor(sf::Color::Magenta);
	bound.setOutlineThickness(1);
	bound.setFillColor(sf::Color(255, 255, 255, 0));

}

void Zombie::Release()
{
	SpriteGo::Release();
}

void Zombie::Reset()
{
	SpriteGo::Reset();
	//플레이어 할당 : Create에서 했다.
}

void Zombie::Update(float dt)
{
	atkTimer += dt;
	SpriteGo::Update(dt);

	direction = player->GetPosition() - position;
	Utils::Normalize(direction);

	//기어다니는 친구
	if (type == Types::Crawler)
	{
		speed += (speed * 5.f + 1.f) * dt;
		if (speed > maxSpeed)
			speed = maxSpeed;
	}

	//플레이어에게 이동
	if (distanceToPlayer > GetBound().getRadius())
	{
		//SetPosition(GetPosition() + Utils::GetNormalize(player->GetPosition() - GetPosition()) * speed * dt);
		Translate(direction * speed * dt);
		if (type == Types::Crawler && speed >= maxSpeed)
		{
			speed = 0.f;
			atkTimer = 0.f;
		}
	}

	//충돌 검사
	Collision(dt);

	direction = player->GetPosition() - position;
	Utils::Normalize(direction);

}

void Zombie::FixedUpdate(float dt)
{

	distanceToPlayer = Utils::Distance(player->GetPosition(), position);
	SpriteGo::FixedUpdate(dt);
	if (atkTimer >= atkInterval && distanceToPlayer <= GetBound().getRadius())
	{
		player->onDamage(atkDamage);
		atkTimer = 0.f;
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}

void Zombie::DebugUpdate(float dt)
{
	bound.setPosition(position);
}

void Zombie::DebugDraw(sf::RenderWindow& window)
{
	window.draw(bound);
}

//충돌
void Zombie::Collision(float dt)
{
	//좀비
	for (auto ptr : dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->zombieObjects)
	{
		if (ptr == this)
			continue;
		sf::Vector2f dz = Utils::GetNormalize(ptr->GetPosition() - position); //다른 좀비로의 방향
		float distance = Utils::Distance(ptr->GetPosition(), position); //다른 좀비와의 거리
		float minDistance = GetBound().getRadius() + ptr->GetBound().getRadius(); //최소 거리
		if (distance < minDistance)
		{
			SetPosition(position - dz * speed * 2.f * dt);
		}
	}

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
	rotation = Utils::Angle(player->GetPosition() - GetPosition());
	SetRotation(rotation);
}

void Zombie::OnDie()
{
	isDead = true;
	SCENE_MGR.GetCurrentScene()->DeleteGo(this);
	SOUND_MGR.PlaySfx("sound/splat.wav");
	switch (Utils::RandomRange(0, 2))
	{
	case 0:
		Item::Create(Item::Types::EXP, scene)->SetPosition(position);
		break;
	case 1:
		Item::Create(Item::Types::AMMO, scene)->SetPosition(position);
		break;
	default:
		break;
	};
}

bool Zombie::Damaged(int damage)
{
	int preHp = hp;
	hp -= damage;
	SCENE_MGR.GetCurrentScene()->AddGo(new EffectBlood(this->position))->Init();
	if (hp <= 0 && !isDead)
	{
		hp = 0;
		OnDie();
	}
	return isDead;
}