#include "pch.h"
#include "Flame.h"
#include "Player.h"

Flame::Flame(Player* player, const std::string& name)
    : Projectile(name), attackAngle(10)
{
	damage = 34;
    sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld((sf::Vector2i)InputMgr::GetMousePos());
    SetPosition(player->GetPosition());
    Utils::Normalize(direction = mouseWorldPos - position);

    shape.setSize({ 50.f, 50.f });
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
    //shape.setPosition(player->GetPosition());
}

void Flame::Draw(sf::RenderWindow& window)
{
    Projectile::Draw(window);
    window.draw(shape);
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
    std::cout << angle <<std::endl;
    float distance = Utils::Distance(position, zombie->GetPosition());

    if (angle < attackAngle && distance < attackRadius)
    {
        return true;
    }

    return false;
}