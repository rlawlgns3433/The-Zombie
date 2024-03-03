#include "pch.h"
#include "ZombieSpawner.h"
#include "SceneGame.h"

ZombieSpawner::ZombieSpawner(const std::string& name)
	:Spawner(name)
{
}

ZombieSpawner::ZombieSpawner(Scene* sc, const std::string& name)
	:Spawner(sc, name)
{
}

void ZombieSpawner::Reset()
{
	Spawner::Reset();
}

void ZombieSpawner::AddType(Zombie::Types type)
{
	zombieTypes.push_back(type);
}

GameObject* ZombieSpawner::Create()
{
	Zombie::Types zombieType = zombieTypes[Utils::RandomRange(0, zombieTypes.size())];
	return Zombie::Create(zombieType, scene);
}
