#pragma once
#include "Scene.h"
#include "Zombie.h"
#include <fstream>
#include <sstream>

class Player;
class Bullet;
class Flame;
class TileMap;
class Spawner;
class UIHUD;
class Crosshair;
class Projectile;
class UILevelUp;

class SceneGame : public Scene
{
public:
	enum class Status
	{
		PLAY,
		PAUSE,
		DIE,
		LEVELUP,
		WIN
	};
	Status status = Status::PLAY;
	UILevelUp* uiLevel;
protected:

	Player* player;
	UIHUD* hud;
	TileMap* tileMap;

	std::vector<Spawner*> spawners;
	std::vector<std::string> highScore;

	float playTimer;
	
	float fastestTime = 0.f;
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
	std::list<Projectile*> bullets;

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

	void SetStatus(Status st);
	void AddScore(int s);

	inline Player* GetPlayer() { return player; }
	inline const std::pair<sf::Vector2f, sf::Vector2f>& GetBoundary() const { return boundary; }

	//Wave
	void ChangeWave(int w);
	void ReleaseWave();
	void InitWave();

	UIHUD* GetHUD() { return this->hud; }
	void SaveHighScore();
	int GetHighScore();
};

