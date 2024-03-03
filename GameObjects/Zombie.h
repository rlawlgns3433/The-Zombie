#pragma once
#include "SpriteGo.h"
#include "Player.h"

class Zombie : public SpriteGo
{
public:
	enum class Types
	{
		Chaser,
		Bloater,
		Crawler,
		TIMBER_BOSS,
		Count,
	};
	static Zombie* Create(Types zombieType, Scene* sc);
	static const int TotalTypes = (const int)Types::Count;


protected:
	Types type;
	
	int maxHp = 1;
	float maxSpeed = 1;

	float speed = 1;
	int hp = 1;
	int atkDamage = 1;
	float atkInterval = 1.f;
	float atkTimer = 0.f;


	Player* player;
	float distanceToPlayer;
	sf::Vector2f direction;
	sf::CircleShape bound;

	Zombie(const std::string& name="");
	Zombie(Scene* sc, const std::string& name="");

	void Collision(float dt);

public:
	void OnDie();
	bool isDead = false;

	~Zombie() override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void DebugUpdate(float dt) override;
	void DebugDraw(sf::RenderWindow& window) override;

	inline float GetDistanceToPlayer() const { return distanceToPlayer; }
	inline void SetPlayer(Player* p) { player = p; }
	bool Damaged(int damage);
	const sf::Vector2f& GetDirection() const { return direction; };
	int GetHp() { return hp; };

	//radius
	inline const sf::CircleShape& GetBound() { return bound; }

};