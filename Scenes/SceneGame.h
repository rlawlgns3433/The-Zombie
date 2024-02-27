#pragma once
#include "Scene.h"
#include "Zombie.h"


class Player;
class Bullet;
class TileMap;
class Spawner;
class UIHUD;
class Crosshair;

class SceneGame : public Scene
{
protected:
	enum class Status
	{
		PLAY,
		PAUSE,
	};
	Status status = Status::PLAY;

	Player* player;
	UIHUD* hud;
	TileMap* tileMap;

	std::vector<Spawner*> spawners;

	int score = 0;
	int hiScore = 0;
	int wave = 0;
	int zombieCount = 1;
	std::pair<sf::Vector2f, sf::Vector2f> boundary;

	bool doReset = false;

	void BulletCollision(float dt);
	sf::Vector2f GetBoundaryCenter();

	sf::Text* debugZombieCount = nullptr;

public:
	//sf::Vector2f ClampByTileMap(const sf::Vector2f& point);
	std::list<Zombie*> zombieObjects;
	std::list<Bullet*> bullets;
	Crosshair* crosshair = nullptr;


	SceneGame(SceneIds id);
	~SceneGame() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;


	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void DebugUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	inline Player* GetPlayer() { return player; }
	inline const std::pair<sf::Vector2f, sf::Vector2f>& GetBoundary() const { return boundary; }

	void AddScore(int s);

	void ChangeWave(int w);
	void ReleaseWave();
	void InitWave();

	UIHUD* GetHUD() { return this->hud; }
};

