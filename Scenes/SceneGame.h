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
class ZombieBoss;

class SceneGame : public Scene
{
public:
	enum class Status
	{
		PLAY,
		PAUSE,
		DIE,
		LEVELUP
	};
	Status status = Status::PLAY;
	UILevelUp* uiLevel;
private:
	//콤보
	InputMgr::SFGM_COMBO cheatExp;
	void CheatExp();
	InputMgr::SFGM_COMBO cheatHp;
	void CheatHp();
	InputMgr::SFGM_COMBO cheatKill;
	void CheatKill();
	InputMgr::SFGM_COMBO cheatWin;
	void CheatWin();
	InputMgr::SFGM_COMBO cheatBoss;
	void CheatBoss();

protected:

	SceneGame(const SceneGame&) = delete;
	SceneGame(SceneGame&&) = delete;
	SceneGame& operator=(const SceneGame&) = delete;
	SceneGame& operator=(SceneGame&&) = delete;

	Player* player;
	UIHUD* hud;
	TileMap* tileMap;
	ZombieBoss* zombieBoss = nullptr;
	bool zombieBossDead = false;

	std::vector<Spawner*> spawners;
	std::vector<std::string> highScore;

	float playTimer = 0.f;
	float fastestTime = 0.f;

	int score = 0;
	int hiScore = 0;
	int wave = 0;
	int zombieCount = 1;

	std::pair<sf::Vector2f, sf::Vector2f> boundary;

	bool doReset = false;
	bool isWin = false;
	float killTimer = 0.f;
	float winTimer = 0.f;

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
	void WinAnimation(float dt);
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void DebugUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void SetStatus(Status st);
	void AddScore(int s);

	inline Player* GetPlayer() { return player; }
	inline ZombieBoss* GetZomieBoss() { return zombieBoss; }

	void SetZombieBossDead(bool dead) { zombieBossDead = dead; }
	bool GetZombieBossDead() { return zombieBossDead;}

	inline const std::pair<sf::Vector2f, sf::Vector2f>& GetBoundary() const { return boundary; }

	//Wave
	void ChangeWave(int w);
	void ReleaseWave();
	void InitWave();

	UIHUD* GetHUD() { return this->hud; }
	void SaveHighScore(); //CHECK SceneScore에서 저장할 예정
	int GetHighScore();

	void Win();
};

