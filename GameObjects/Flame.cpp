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


    //debug
    SetBound();
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
    //sprite.setPosition(player->GetPosition());

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

void Flame::DebugDraw(sf::RenderWindow& window)
{
    Projectile::DebugDraw(window);
    window.draw(bound);
}

void Flame::Hit()
{
    //비어있어야 합니다.
}

void Flame::EndOfCheckZombie()
{
    isHit = true;
}

void Flame::Create(Scene* scene, Player* player)
{
    SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
    int count = player->GetWeapon()->GetProjectileCount();
    auto flameList = Utils::FanSpread(player->GetLook(), count, 40.f/count*2);

    auto ptr = flameList.begin();
    for (int i = 0; i < count; i++)
    {
        Flame* flame = new Flame(player);
        flame->Init();
        flame->Reset();
        flame->damage = player->GetWeapon()->GetDamage();
        flame->SetDirection(*(ptr++));
        flame->scene = scene;
        flame->player = player;
        sceneGame->AddGo(flame);
        sceneGame->bullets.push_back(flame);
    }
}

void Flame::SetDirection(sf::Vector2f direc)
{
    Projectile::SetDirection(direc);
    sprite.setRotation(Utils::Angle(direc)-90);
    SetBound();
}

void Flame::SetBound()
{
    int count = 10;
    bound = sf::VertexArray(sf::LinesStrip, count);
    bound[0].position = position;
    bound[9].position = position;
    bound[0].color = sf::Color::Magenta;
    bound[9].color = sf::Color::Magenta;

    auto direc = Utils::FanSpread(direction, count-2, attackAngle*2 / (count-2));
    auto it = direc.begin();

    for (int i = 1; i < count-1; i++)
    {
        bound[i].position = position + (*it) * attackRadius;
        bound[i].color = sf::Color::Magenta;
        it++;
    }
}

bool Flame::CheckCollision(Zombie* zombie)
{
    float distance = Utils::Distance(position, zombie->GetPosition())-zombie->GetBound().getRadius();

    if (distance > attackRadius)
    {
        return false;
    }

    float angle = Utils::Angle(direction, zombie->GetPosition() - position);
    if (angle > attackAngle)
    {
        return false;
    }
    return true;
}