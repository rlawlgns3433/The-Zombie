#pragma once
#include "GameObject.h"

class Player;
class SceneGame;

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
	SceneGame* sceneGame = nullptr;

	Types type;

	float attackInterval = 1.f;
	int damage = 0;

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
};