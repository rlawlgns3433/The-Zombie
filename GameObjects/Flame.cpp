#include "pch.h"
#include "Flame.h"
#include "Player.h"
#include "SceneGame.h"

Flame::Flame(Player* player, const std::string& name)
    : Projectile(name), attackAngle(40)
{
	//damage = 34;
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

void Flame::Create(Scene* scene, Player* player)
{
    SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
    int count = player->GetWeapon()->GetProjectileCount();
    auto flameList = Utils::FanSpread(player->GetLook(), count, 60.f/(count/2));

    auto ptr = flameList.begin();
    for (int i = 0; i < count; i++)
    {
        Flame* flame = new Flame(player);
        flame->Init();
        flame->Reset();
        flame->damage = player->GetWeapon()->GetDamage();
        flame->SetDirection(*(ptr++));
        flame->scene = scene;
        sceneGame->AddGo(flame);
        sceneGame->bullets.push_back(flame);
    }
}

void Flame::SetDirection(sf::Vector2f direc)
{
    Projectile::SetDirection(direc);
    sprite.setRotation(Utils::Angle(direc)-90);
}

bool Flame::CheckCollision(Zombie* zombie)
{
    float angle = Utils::Angle(direction, zombie->GetPosition() - position);
    if (angle > attackAngle)
    {
        return false;
    }

    float distance = Utils::Distance(position, zombie->GetPosition());

    if (distance > attackRadius)
    {
        return false;
    }

    return true;
}