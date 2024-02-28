#include "pch.h"
#include "ItemSpawner.h"
#include "SceneGame.h"

ItemSpawner::ItemSpawner(const std::string& name)
	:Spawner(name)
{
	interval = 5.f; //주기
	spawnCount = 2;
	radius = 500.f;
	timer = 0.f;
	//생성시에 값을 받을 수 있도록 or 랜덤
}

ItemSpawner::ItemSpawner(Scene* sc, const std::string& name)
	:Spawner(sc, name)
{
	//TODO 외부에서 멤버변수 수정할 수 있게
	interval = 5.f;
	spawnCount = 2;
	radius = 500.f;
	timer = 0.f;
}

void ItemSpawner::Reset()
{
	itemTypes.clear();
	itemTypes.push_back(Item2::Types::HEALTH);
	itemTypes.push_back(Item2::Types::AMMO);
	itemTypes.push_back(Item2::Types::AMMO);
	itemTypes.push_back(Item2::Types::AMMO);
	itemTypes.push_back(Item2::Types::AMMO);

	Spawner::Reset();
}

GameObject* ItemSpawner::Create()
{
	Item2::Types itemType = itemTypes[Utils::RandomRange(0, itemTypes.size())];
	int val = 0;
	switch (itemType)
	{

	case Item2::Types::AMMO:
		val = Utils::RandomRange(20, 40);
		break;
	case Item2::Types::HEALTH:
		val = Utils::RandomRange(10, 30);
		break;
	default:
		break;
	}

	Item2* go = Item2::Create(itemType, val, scene);

	return go;
}