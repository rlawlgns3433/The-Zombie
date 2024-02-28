#pragma once
#include "Projectile.h"
class Flame : public Projectile
{
protected :
	float attackAngle;

public :
    Flame(const sf::Vector2f& position, const std::string& name = "bullet");
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