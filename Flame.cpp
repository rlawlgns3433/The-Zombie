#include "pch.h"
#include "Flame.h"
#include "Player.h"

Flame::Flame(Player* player, const std::string& name)
    : Projectile(name), attackAngle(45)
{
	damage = 34;
    sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld((sf::Vector2i)InputMgr::GetMousePos());
    Utils::Normalize(direction = mouseWorldPos - position);
    SetPosition(position + direction * 20.f);
}

void Flame::Init()
{
    Projectile::Init();
}

void Flame::Release()
{
    Projectile::Release();
}

void Flame::Reset()
{
    Projectile::Reset();
}

void Flame::Update(float dt)
{
    Projectile::Update(dt);
}

void Flame::Draw(sf::RenderWindow& window)
{
}

Flame* Flame::Create(Player* player)
{
    Flame* flame = new Flame(player);
    flame->Init();
    return nullptr;
}

bool Flame::CheckCollision(Zombie* zombie)
{
    float angle = Utils::Angle(direction, zombie->GetPosition() - position);
    float distance = Utils::Distance(position, zombie->GetPosition());

    if (angle < attackAngle && distance < attackRadius)
    {
        return true;
    }
    return false;
}