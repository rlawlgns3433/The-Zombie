#pragma once
#include "DataTable.h"
#include "Zombie.h"


struct DataLevelUp
{
	int id;

	std::wstring name;
	std::wstring desc;
	std::wstring effect;
	std::string textureId;

	int weight;

	int maxHp;
	float speed;
	float xExp; //경험치 배율
	int damage;
	float shotInterval;
	float reloadInterval;
	int maxAmmo;
	int weaponUp;
	int projectile;

};


class LevelUpTable : public DataTable
{
protected:
	std::unordered_map<int, DataLevelUp> table;
	std::vector<int> indexList;

public:

	LevelUpTable(DataTable::Types t);
	~LevelUpTable() override;
	LevelUpTable(const LevelUpTable&) = delete;
	LevelUpTable(LevelUpTable&&) = delete;
	LevelUpTable& operator=(const LevelUpTable&) = delete;
	LevelUpTable& operator=(LevelUpTable&&) = delete;

	bool Load() override;
	void Release() override;

	const DataLevelUp& Get();
	
};
