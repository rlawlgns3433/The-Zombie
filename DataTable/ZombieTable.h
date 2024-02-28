#pragma once
#include "DataTable.h"
#include "Zombie.h"

struct DataZombie
{
	Zombie::Types id;

	std::string nameId;
	std::string descriptionId;
	std::string textureId;

	int maxHp;
	float maxSpeed;
	int atkDamage;
	float atkInterval;
};


class ZombieTable : public DataTable
{
	static DataZombie unDef;
protected:
	std::unordered_map<Zombie::Types, DataZombie> table;

public:
	ZombieTable(DataTable::Types t);
	~ZombieTable() override;

	bool Load() override;
	void Release() override;

	const DataZombie& Get(Zombie::Types id);
};

