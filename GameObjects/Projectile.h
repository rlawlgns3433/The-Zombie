#pragma once
#include "GameObject.h"
#include "Zombie.h"

class Projectile : public GameObject
{
protected:
	Projectile(const Projectile&) = delete;
	Projectile(Projectile&&) = delete;
	Projectile& operator=(const Projectile&) = delete;
	Projectile& operator=(Projectile&&) = delete;

	sf::Vector2f direction;
	int damage = 1;

public:
	bool isHit = false;

	Projectile(const std::string& name = "");
	~Projectile() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	int GetDamage() const { return damage; }
	void SetDamage(int damage) { this->damage = damage; }
	virtual void Hit();
	virtual void EndOfCheckZombie() {};
	virtual bool CheckCollision(Zombie* zombie) = 0;

};