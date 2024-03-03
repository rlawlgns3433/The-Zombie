#pragma once
#include "SpriteGo.h"
#include "ShapeGo.h"

class Player;
class BossRangeSkill;

class ZombieBoss : public SpriteGo
{
	enum class STATUS
	{
		MOVE,
		RANGESKILL,
		BINDING_SKILL,
	};

protected:
	STATUS currentStatus;
	
	ShapeGo<sf::RectangleShape>* hpBar;
	ShapeGo<sf::RectangleShape>* hpBarBlack;
	//sf::RectangleShape hpBar;
	sf::Vector2f hpBarSize;

	std::list<BossRangeSkill*> useRangeSkill;
	std::list<BossRangeSkill*> unuseRangeSkill;

	int maxHp = 3000;
	float maxSpeed = 1000;
	float speed = 100;
	int hp = 3000;
	int atkDamage = 30;
	float atkInterval = 1.f;
	float atkTimer = 0.f;

	float rangeSkillTime = 3.f;
	float rangeSkillTimer = 0.f;

	Player* player;
	float distanceToPlayer;
	sf::Vector2f direction;
	sf::CircleShape bound; //TODO 히트박스 정보 옮기기

	int rangeSkillCount = 0;
	int rangeSkillCountMax = 3;

	float rangeSkillDT = 0.3f;
	float rangeSkillDuration = 0.3f;

public:
	static ZombieBoss* Create(Scene* sc);

	std::list<BossRangeSkill*>& GetUseRangeSkill()
	{
		return useRangeSkill;
	}

	std::list<BossRangeSkill*>& GetUnUseRangeSkill()
	{
		return unuseRangeSkill;
	}

	bool isDead = false;

	ZombieBoss(const std::string& name = "");
	ZombieBoss(Scene* sc , const std::string& name = "");
	~ZombieBoss() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void SetHp(int hp, int max);

	void DebugUpdate(float dt) override;
	void DebugDraw(sf::RenderWindow& window) override;

	void RangeSkill();

	inline float GetDistanceToPlayer() const
	{
		return distanceToPlayer;
	}

	inline void SetPlayer(Player* p)
	{
		player = p;
	}

	bool Damaged(int damage);

	const sf::Vector2f& GetDirection() const
	{
		return direction;
	};

	int GetHp()
	{
		return hp;
	};

	//radius
	inline const sf::CircleShape& GetBound()
	{
		return bound;
	}

	void Collision(float dt);
	void OnDie();
};

