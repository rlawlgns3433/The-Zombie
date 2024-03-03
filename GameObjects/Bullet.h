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

    sf::Vector2f prePos;
    sf::RectangleShape shape;
    sf::RectangleShape bound;

    Bullet(const sf::Vector2f& position, const std::string& name = "bullet");
    ~Bullet() = default;

    Bullet(const Bullet&) = delete;
    Bullet(Bullet&&) = delete;
    Bullet& operator=(const Bullet&) = delete;
    Bullet& operator=(Bullet&&) = delete;


    void Init()override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void DebugUpdate(float dt) override;
    void Draw(sf::RenderWindow& window) override;
    void DebugDraw(sf::RenderWindow& window) override;

    void SetDirection(sf::Vector2f direc) override;

    static void Create(Scene* sc);

    bool CheckCollision(SpriteGo* zombie) override;
    //bool CheckCollision(ZombieBoss* zombieBoss) override;
};

