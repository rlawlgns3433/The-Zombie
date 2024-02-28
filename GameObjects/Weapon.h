#pragma once
#include "GameObject.h"

class Player;
class SceneGame;
class UIHUD;

class Weapon : public GameObject
{
public:
	enum class Types
	{
		Cloased,	// 근점
		Ranged,		// 원기리
	};
	static const int totalTypes = 2;

protected:
	Weapon(const Weapon&) = delete;
	Weapon(Weapon&&) = delete;
	Weapon& operator=(const Weapon&) = delete;
	Weapon& operator=(Weapon&&) = delete;

	Player* player = nullptr;
	UIHUD* hud = nullptr;
	Types type;

	float shotInterval = 0.05f;
	float shotTimer = 0.f;
	float reloadSpeed = 1.f;

	int damage = 0;

	int maxAmmo = 26;
	int ammo = maxAmmo;
	int totalAmmo = ammo;

public:
	Weapon(const std::string& name = "");
	~Weapon() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void AddMaxAmmo(int value);
	void AddShotInterval(float value);
	void AddDamage(int value);
	void AddReloadSpeed(float value);

	virtual void Attack() = 0;
	void AddTotalAmmo(int add) { totalAmmo += add; }
	int GetAmmo() const { return this->ammo; }
	int GetTotalAmmo() const { return this->totalAmmo; }
};