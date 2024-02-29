#pragma once
#include "Spawner.h"
#include "Zombie.h"

class ZombieSpawner : public Spawner
{
protected:
	std::vector<Zombie::Types> zombieTypes;


public:
	ZombieSpawner(const std::string& name = "ZombieSpawner");
	ZombieSpawner(Scene* sc, const std::string& name = "ZombieSpawner");
	~ZombieSpawner()override =default;

	void Reset() override;


	void AddType(Zombie::Types type);

	GameObject* Create() override;
};