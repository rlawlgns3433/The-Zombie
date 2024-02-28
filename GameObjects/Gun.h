#pragma once
#include "Weapon.h"

class UIHUD;

class Gun : public Weapon
{
protected:
	Gun(const Gun&) = delete;
	Gun(Gun&&) = delete;
	Gun& operator=(const Gun&) = delete;
	Gun& operator=(Gun&&) = delete;

	UIHUD* hud = nullptr;

	int maxAmmo = 26;
	int ammo = maxAmmo;
	int totalAmmo = ammo;

	float shotInterval = 0.05f;

	float shotTimer = 0.f;
	bool isFiring = false;

public :
	Gun(Player* player, const std::string& name = "");
	~Gun() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Attack() override;
	void Reload();

	void AddTotalAmmo(int add);
	int GetAmmo() const { return this->ammo; }
	int GetTotalAmmo() const { return this->totalAmmo; }
};

