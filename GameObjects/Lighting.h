#pragma once
#include "Projectile.h"
class Lighting : public Projectile
{
protected:

public:
    sf::VertexArray lines;
    sf::Sprite circle;

    std::list<SpriteGo*> zombies;
    std::vector<SpriteGo*> sortedZombies;

    sf::Vector2f firstPos;

    int maxHit = 5;
    int hitCount = 0;
    float timer = 1.f;
    bool isDischarge = false;

    float damageTimer = 0.f;
    float damageInterval = 0.2f;
    float damageDecrease = 0.5f;

    Lighting(Scene* sc, const std::string& name = "Lighting");
    ~Lighting();


    void Init() override;
    void Reset() override;
    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void Draw(sf::RenderWindow& window) override;


    bool CheckCollision(SpriteGo* zombie) override;

    static void Create(Scene* sc);

    void Hit() override;
    void EndOfCheckZombie() override;
    void Discharge();
    void SortAndSetPosition();
    void DamageDecrease();

};

