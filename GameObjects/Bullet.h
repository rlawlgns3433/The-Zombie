#pragma once
#include "Projectile.h"

class Player;

class Bullet : public Projectile
{
protected:
    float speed;
    float displacement = 0.f; //움직인 거리
    float isStuckInWall = false;

public:
    bool isHit = false;
    sf::Vector2f prePos;
    sf::RectangleShape shape;

    Bullet(const sf::Vector2f& position, const std::string& name = "bullet");
    ~Bullet() = default;


    void Init()override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
    
    void Hit();

    static Bullet* Create(Player* player);

    // Projectile을(를) 통해 상속됨
    bool CheckCollision(Zombie* zombie) override;
};

