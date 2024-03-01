#pragma once
#include "SpriteGo.h"

class Player;
class ZombieBoss;

class BossRangeSkill : public SpriteGo
{

protected:
	sf::Vector2f direction;
	ZombieBoss* zombieBoss = nullptr;
	Player* player = nullptr;
	float speed = 1.5f;
	bool hit = false;

	float dtime = 0.f;
	float unUseListTime = 10.f;

public:
	static BossRangeSkill* Create();

	BossRangeSkill(const std::string& name = "");
	~BossRangeSkill() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void DebugUpdate(float dt) override;
	void DebugDraw(sf::RenderWindow& window) override;



};

