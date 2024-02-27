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
	return Item2::Create(itemType, val);
}