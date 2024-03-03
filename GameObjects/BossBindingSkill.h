#pragma once
#include "SpriteGo.h"
#include "ShapeGo.h"

class Player;
class ZombieBoss;
class TextGo;

class BossBindingSkill : public SpriteGo
{
protected:
	Player* player = nullptr;
	ZombieBoss* zombieBoss = nullptr;
	TextGo* binding = nullptr;
	ShapeGo<sf::RectangleShape>* bindingGauge = nullptr;

	sf::Vector2f bindingGaugeMaxSize;
	sf::Vector2f playerPos;
	float speed = 30.f;

	int addGauge = 50;
	bool isBinding = false;

public:
	BossBindingSkill(const std::string& name = "");
	~BossBindingSkill();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void DebugUpdate(float dt) override;
	void DebugDraw(sf::RenderWindow& window) override;

	void BindingSkill();
};

