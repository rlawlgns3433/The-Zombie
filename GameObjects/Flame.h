#pragma once
#include "Projectile.h"

class Player;

class Flame : public Projectile
{
protected :
	float attackAngle;
    float attackRadius = 200;
    //sf::RectangleShape shape;
    sf::Sprite sprite;
    Player* player = nullptr;

    float attackDuration = 0.1f;
    float attackTimer = 0.f;

public :
    Flame(Player* player, const std::string& name = "flame");
    ~Flame() = default;

    void Init()override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
    void Hit() override;
    void EndOfCheckZombie();
    static Flame* Create(Scene* scene, Player* player);

    bool CheckCollision(Zombie* zombie) override;
};