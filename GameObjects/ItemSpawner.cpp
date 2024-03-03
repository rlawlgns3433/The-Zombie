#include "pch.h"
#include "ItemSpawner.h"
#include "SceneGame.h"
#include "ItemTable.h"

ItemSpawner::ItemSpawner(const std::string& name)
	:Spawner(name)
{
	//아이템 스포너 수치는 고정.
	//추후 아이템이 추가될 때 변경.
	interval = 5.f;
	spawnCount = 2;
	radius = 500.f;
	timer = 0.f;
}

ItemSpawner::ItemSpawner(Scene* sc, const std::string& name)
	:Spawner(sc, name)
{
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