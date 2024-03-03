#include "pch.h"
#include "SwordAttack.h"
#include "Player.h"
#include "SceneGame.h"
#include "ZombieBoss.h"

SwordAttack::SwordAttack(Player* player, const std::string& name)
	: Projectile(name), attackAngle(90)
{
    //damage = 34;
    sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld((sf::Vector2i)InputMgr::GetMousePos());
    SetPosition(player->GetPosition());
    Utils::Normalize(direction = mouseWorldPos - position);

    sprite.setTexture(RES_MGR_TEXTURE.Get("graphics/reddeath/sword_attack.png"));
    sprite.setRotation(Utils::Angle(player->GetLook()) - 90);
    sprite.setPosition(player->GetPosition());
    sprite.setScale({ attackRadius / 60.f , attackRadius / 60.f });
    Utils::SetOrigin(sprite, Origins::TC);
}

void SwordAttack::Init()
{
    Projectile::Init();
    scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
}

void SwordAttack::Release()
{
    Projectile::Release();
}

void SwordAttack::Reset()
{
    Projectile::Reset();
}

void SwordAttack::Update(float dt)
{
    Projectile::Update(dt);

    attackTimer += dt;
    if (attackTimer > attackDuration)
    {
        scene->DeleteGo(this);
    }
}

void SwordAttack::Draw(sf::RenderWindow& window)
{
    Projectile::Draw(window);
    window.draw(sprite);
}

void SwordAttack::Hit()
{
    
}

void SwordAttack::EndOfCheckZombie()
{
    isHit = true;
}

SwordAttack* SwordAttack::Create(Scene* scene, Player* player)
{
    SwordAttack* swordAttack = new SwordAttack(player);
    swordAttack->Init();
    return swordAttack;
}

bool SwordAttack::CheckCollision(SpriteGo* zombie)
{
    float angle = Utils::Angle(direction, zombie->GetPosition() - position);
    std::cout << angle << std::endl;
    float distance = Utils::Distance(position, zombie->GetPosition());

    if (angle < attackAngle && distance < attackRadius)
    {
        return true;
    }

    return false;
}
