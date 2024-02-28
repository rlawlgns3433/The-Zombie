#include "pch.h"
#include "ItemSpawner.h"
#include "SceneGame.h"
#include "ItemTable.h"

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
	itemTypes.push_back(Item::Types::HEALTH);
	itemTypes.push_back(Item::Types::AMMO);
	itemTypes.push_back(Item::Types::AMMO);
	itemTypes.push_back(Item::Types::AMMO);
	itemTypes.push_back(Item::Types::AMMO);

	Spawner::Reset();
}

GameObject* ItemSpawner::Create()
{
	Item::Types itemType = itemTypes[Utils::RandomRange(0, itemTypes.size())];
	const DATA_ITEM& data = DT_ITEM->Get(itemType);

	int val = Utils::RandomRange(data.minVal, data.maxVal);
	Item* go = Item::Create(itemType, scene, val);

	return go;
}