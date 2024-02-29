#include "pch.h"
#include "Flame.h"
#include "Player.h"
#include "SceneGame.h"

Flame::Flame(Player* player, const std::string& name)
    : Projectile(name), attackAngle(40)
{
	damage = 34;
    sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld((sf::Vector2i)InputMgr::GetMousePos());
    SetPosition(player->GetPosition());
    Utils::Normalize(direction = mouseWorldPos - position);

    sprite.setTexture(RES_MGR_TEXTURE.Get("graphics/flame.png"));
    sprite.setRotation(Utils::Angle(player->GetLook()) - 90);
    sprite.setPosition(player->GetPosition());
    sprite.setScale({ attackRadius / 60.f , attackRadius / 60.f});
    Utils::SetOrigin(sprite, Origins::TC);
}

void Flame::Init()
{
    Projectile::Init();
    scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
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

    attackTimer += dt;
    if (attackTimer > attackDuration)
    {
        scene->DeleteGo(this);
    }
}

void Flame::Draw(sf::RenderWindow& window)
{
    Projectile::Draw(window);
    window.draw(sprite);
}

void Flame::Hit()
{
    
}

void Flame::EndOfCheckZombie()
{
    isHit = true;
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