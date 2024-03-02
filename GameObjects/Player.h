#pragma once
#include "SpriteGo.h"

class TileMap;
class Item;
class UIHUD;
class Gun;
class FlameThrower;
class Sword;
class Weapon;

struct DataLevelUp;

class Sword;

class Player : public SpriteGo
{
public:
	enum class TYPES
	{
		MAN,
		FIREBAT,
		READDEATH,
		MAGE,
		COUNT
	};

protected:
	sf::Vector2f direction;
	sf::Vector2f look = { 1.f, 0.f };
	sf::CircleShape bound;
	std::pair<sf::Vector2f, sf::Vector2f> boundary;

	TYPES type = TYPES::FIREBAT;

	int level = 1;
	int maxExp = 20;
	int currentExp = 0;
	float xExp = 1.f;
	int maxHp = 100;
	int hp = 100;
	float speed = 300.f;

	float damagedInterval = 0.2f;
	float damagedTimer = 0.f;

	bool isLevelUp = false;
	bool invincibility = false;

	TileMap* tileMap = nullptr;
	UIHUD* hud = nullptr;
	Weapon* weapon = nullptr;
	std::string textureId = "graphics/player.png";

public:

	Player(const std::string& name);
	~Player() override = default;
	Player(const Player&) = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void DebugUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void DebugDraw(sf::RenderWindow& window) override;

	void OnDie();
	void onItem(Item* item);
	void OnDamage(int damage);
	void RangeOnDamage(int damage);

	//레벨업 하면 true 반환
	void AddExp(int value);
	void AddStat(DataLevelUp data);
	void AddHp(int value);
	void LevelUp();

	void SetPlayerType(Player::TYPES type);

	inline const sf::CircleShape& GetBound() const { return bound; }
	inline int GetLevel() const { return level; }
	inline int GetHp() const { return hp; }
	inline int GetMaxHP() const { return maxHp; }
	inline float GetSpeed() const { return speed; }
	inline sf::Vector2f GetLook() const { return look; }
	inline void SetSpeed(float s) { speed = s; }
	inline void SetInvincibility(bool value) { invincibility = value; }
	inline void SetInvincibility() { invincibility = !invincibility; }

	TYPES GetWeaponType() { return type; }
	Weapon* GetWeapon() { return weapon; }
};

