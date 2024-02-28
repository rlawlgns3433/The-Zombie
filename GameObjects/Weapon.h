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

	int level = 1;

	float shotInterval = 1.f;
	float shotTimer = 0.f;
	float reloadSpeed = 1.f; //time to shot

	int damage = 1;
	int projectileCount = 3;

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

	virtual void Attack() = 0;

	void AddMaxAmmo(int value);
	void AddTotalAmmo(int add);
	void AddShotInterval(float value);
	void AddDamage(int value);
	void AddReloadSpeed(float value);
	void AddProjectile(int value);
	inline void AddLevel(int value) { level += value; }

	inline void SetDamage(int value) { damage = value; }

	inline int GetAmmo() const { return ammo; }
	inline int GetTotalAmmo() const { return totalAmmo; }
	inline int GetDamage() const { return damage; }
	inline int GetProjectileCount() const { return projectileCount; }
};