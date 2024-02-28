#pragma once
#include "Weapon.h"

class UIHUD;

class Sword : public Weapon
{
protected:
	Sword(const Sword&) = delete;
	Sword(Sword&&) = delete;
	Sword& operator=(const Sword&) = delete;
	Sword& operator=(Sword&&) = delete;

	UIHUD* hud = nullptr;

	//bool isFiring = false;

public:
	Sword(Player* player, const std::string& name = "");
	~Sword() override = default;

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

