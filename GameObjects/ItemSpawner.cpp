#include "pch.h"
#include "ItemSpawner.h"
#include "SceneGame.h"

ItemSpawner::ItemSpawner(const std::string& name)
	:Spawner(name)
{
	interval = 5.f; //�ֱ�
	spawnCount = 2;
	radius = 500.f;
	timer = 0.f;
	//�����ÿ� ���� ���� �� �ֵ��� or ����
}

ItemSpawner::ItemSpawner(Scene* sc, const std::string& name)
	:Spawner(sc, name)
{
	//TODO �ܺο��� ������� ������ �� �ְ�
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
	int val = 0;
	switch (itemType)
	{

	case Item::Types::AMMO:
		val = Utils::RandomRange(20, 40);
		break;
	case Item::Types::HEALTH:
		val = Utils::RandomRange(10, 30);
		break;
	default:
		break;
	}

	Item* go = Item::Create(itemType, val, scene);

	return go;
}