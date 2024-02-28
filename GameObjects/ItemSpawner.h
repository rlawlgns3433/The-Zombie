#pragma once
#include "Spawner.h"
#include "Item.h"


class ItemSpawner : public Spawner
{
protected:
	std::vector<Item::Types> itemTypes;

public:
	ItemSpawner(const std::string& name = "ItemSpawner");
	ItemSpawner(Scene* sc, const std::string& name = "ItemSpawner");
	~ItemSpawner()override = default;

	void Reset() override;

	GameObject* Create() override;
};

