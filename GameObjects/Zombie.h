#pragma once
#include "SpriteGo.h"
#include "Player.h"

class Zombie : public SpriteGo
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,

		Count
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
	sf::CircleShape bound; //TODO 히트박스 정보 옮기기

	Zombie(const std::string& name="");
	Zombie(Scene* sc, const std::string& name="");

	void Collision(float dt);
	void OnDie();

public:
	bool isDead = false;

	~Zombie() = default;


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


};