#pragma once
#include "Weapon.h"

class UIHUD;

class FlameThrower : public Weapon
{
protected:
	FlameThrower(const FlameThrower&) = delete;
	FlameThrower(FlameThrower&&) = delete;
	FlameThrower& operator=(const FlameThrower&) = delete;
	FlameThrower& operator=(FlameThrower&&) = delete;

	UIHUD* hud = nullptr;

	int maxAmmo = 26;
	int ammo = maxAmmo;
	int totalAmmo = ammo;

	float shotInterval = 0.1f;
	float shotTimer = 0.f;
	bool isFiring = false;

public:
	FlameThrower(const std::string& name = "");
	~FlameThrower() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Attack() override;
	void Reload();
};

