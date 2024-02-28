#pragma once
#include "Projectile.h"

class Player;

class Flame : public Projectile
{
protected :
	float attackAngle;
    float attackRadius = 300;
    sf::RectangleShape shape;
    Player* player = nullptr;

public :
    Flame(Player* player, const std::string& name = "flame");
    ~Flame() = default;

    void Init()override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    static Flame* Create(Player* player);

    // Projectile을(를) 통해 상속됨
    bool CheckCollision(Zombie* zombie) override;
};