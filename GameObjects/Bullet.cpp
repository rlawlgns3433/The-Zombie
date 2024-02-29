#include "pch.h"
#include "Bullet.h"
#include "Player.h"
#include "SceneGame.h"
#include "Weapon.h"


Bullet::Bullet(const sf::Vector2f& position, const std::string& name)
	:Projectile(name), speed(3000)
{
	//damage = 34;

	shape.setSize({ 3.f, 3.f });
	shape.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(shape, Origins::MR);

	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld((sf::Vector2i)InputMgr::GetMousePos());
	Utils::Normalize(direction = mouseWorldPos - position);
	shape.rotate(Utils::Angle(direction));

	SetPosition(position + direction * 20.f);
	shape.setPosition(this->position);

	shape.setScale({ 0.f , 1.f });
	prePos = position;

	//Debug
	bound.setRotation(Utils::Angle(direction));
	bound.setOutlineColor(sf::Color::Magenta);
	bound.setOutlineThickness(1.f);
}

void Bullet::Init()
{
	Projectile::Init();
}

void Bullet::Release()
{
	Projectile::Release();
}

void Bullet::Reset()
{
	Projectile::Reset();
}

void Bullet::Update(float dt)
{
	if (isStuckInWall) Hit();

	prePos = position;

	Projectile::Update(dt);
	Translate(direction * speed * dt);

	//충돌 검사
	std::pair<sf::Vector2f, sf::Vector2f> boundary = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoundary();
	//충돌 검사: 벽
	if (position.x < boundary.first.x)
	{
		position.y -= (position.x - boundary.first.x) * tan(Utils::DegreeToRadian(Utils::Angle(direction)));
		Utils::ElasticCollision(position.x, boundary.first.x, 0.f);
		isStuckInWall = true;
	}
	if (position.x > boundary.second.x)
	{
		position.y -= (position.x - boundary.second.x) * tan(Utils::DegreeToRadian(Utils::Angle(direction)));
		Utils::ElasticCollision(position.x, boundary.second.x, 0.f);
		isStuckInWall = true;
	}
	if (position.y < boundary.first.y)
	{
		position.x -= (position.y - boundary.first.y) * (1 / tan(Utils::DegreeToRadian(Utils::Angle(direction))));
		Utils::ElasticCollision(position.y, boundary.first.y, 0.f);
		isStuckInWall = true;
	}
	if (position.y > boundary.second.y)
	{
		position.x -= (position.y - boundary.second.y) * (1 / tan(Utils::DegreeToRadian(Utils::Angle(direction))));
		Utils::ElasticCollision(position.y, boundary.second.y, 0.f);
		isStuckInWall = true;
	}

	//총알 궤적
	shape.setPosition(position);
	float distance = Utils::Distance(prePos, position);
	shape.setScale({std::max(1.f,distance / 3.f),1.f });

}

void Bullet::DebugUpdate(float dt)
{
	bound.setSize({ Utils::Distance(prePos, position),0.f });
	Utils::SetOrigin(bound, Origins::MR);
	bound.setPosition(position);

}

void Bullet::Draw(sf::RenderWindow& window)
{
	Projectile::Draw(window);
	window.draw(shape);
	if (isHit)
	{
		active = false;
		scene->DeleteGo(this);
	}
}

void Bullet::DebugDraw(sf::RenderWindow& window)
{
	window.draw(bound);
}

void Bullet::SetDirection(sf::Vector2f direc)
{
	direction = direc;
	bound.setRotation(Utils::Angle(direc));
	shape.setRotation(Utils::Angle(direc));
}

void Bullet::Create(Scene* sc)
{
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(sc);
	Player* player = sceneGame->GetPlayer();
	int count = player->GetWeapon()->GetProjectileCount();

	std::list<Bullet*> bulletList;
	auto bPos = Utils::DressInRow(player->GetPosition(), player->GetLook(), count, 5.f);

	for (auto& ptr : bPos)
	{
		bulletList.push_back(new Bullet(ptr));
	}

	for (auto ptr : bulletList)
	{
		ptr->Init();
		ptr->Reset();
		ptr->damage = player->GetWeapon()->GetDamage();
		ptr->SetDirection(player->GetLook());
		ptr->scene = sc;
		sceneGame->AddGo(ptr);
		sceneGame->bullets.push_back(ptr);
	}

}

bool Bullet::CheckCollision(Zombie* zombie)
{
	return Utils::IsCollideWithLineSegment(zombie->GetPosition(), GetPosition(), prePos, zombie->GetGlobalBounds().width / 3.f);
}
