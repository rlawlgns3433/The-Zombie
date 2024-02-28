#pragma once
#include "SpriteGo.h"

class TileMap;
class Item2;
class UIHUD;
class Gun;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction;
	sf::Vector2f look = { 1.f, 0.f };
	std::pair<sf::Vector2f, sf::Vector2f> boundary;

	int level = 1;
	int maxExp = 20;
	int currentExp = 0;
	int maxHp = 100;
	int hp = 100;
	float speed = 300.f;

	float damagedInterval = 0.4f;
	float damagedTimer = 0.f;

	TileMap* tileMap;
	UIHUD* hud;
	Gun* gun = nullptr;
	std::string textureId = "graphics/player.png";

public:

	Player(const std::string& name);
	~Player() override = default;
	Player(const Player&) = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void onDie();
	void onItem(Item2* item);
	void onDamage(int damage);

	//레벨업 하면 true 반환
	bool AddExp(int value);
	inline void AddMaxHp(int value);
	inline void AddSpeed(float value) { speed += value; }

	inline int GetLevel() const { return level; }
	inline int GetHp() const { return hp; }
	inline int GetMaxHP() const { return maxHp; }
	inline float GetSpeed() const { return speed; }

	Gun* GetGun() { return gun; }
};

