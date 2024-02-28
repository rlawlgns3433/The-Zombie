#pragma once
#include "GameObject.h"
class Projectile : public GameObject
{
protected:
	Projectile(const Projectile&) = delete;
	Projectile(Projectile&&) = delete;
	Projectile& operator=(const Projectile&) = delete;
	Projectile& operator=(Projectile&&) = delete;

	sf::Vector2f direction;

public:
	Projectile(const std::string& name = "");
	~Projectile() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	virtual void CheckCollision() = 0;
};

