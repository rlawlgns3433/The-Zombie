#pragma once
#include "GameObject.h"

class SceneGame;


class Spawner : public GameObject
{
protected:
	float interval = 1.f; //�ֱ�
	int spawnCount = 1;
	int maxCount = -1;
	int currentCount = 0;
	float radius = 400.f;

	float timer = 0.f;

	SceneGame* sceneGame;
	std::pair<sf::Vector2f, sf::Vector2f> boundary;

	virtual GameObject* Create() = 0;

public:
	Spawner(const std::string& name = "");
	Spawner(Scene* sc, const std::string& name = "");
	~Spawner()override = default;

	Spawner(const Spawner&) = delete;
	Spawner(Spawner&&) = delete;
	Spawner& operator=(const Spawner&) = delete;
	Spawner& operator=(Spawner&&) = delete;

	void Init();
	void Release();
	void Reset();
	void Update(float dt);

	void Spawn(int count);

	void SetInterval(float v) { interval = v; }
	void SetSpawnCount(int v) { spawnCount = v; }
	void SetRadius(float v) { radius = v; }
	void SetTimer(float v) { timer = v; }


};