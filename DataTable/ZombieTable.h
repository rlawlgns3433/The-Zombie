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
	ZombieTable(const ZombieTable&) = delete;
	ZombieTable(ZombieTable&&) = delete;
	ZombieTable& operator=(const ZombieTable&) = delete;
	ZombieTable& operator=(ZombieTable&&) = delete;

	bool Load() override;
	void Release() override;

	const DataZombie& Get(Zombie::Types id);
};

