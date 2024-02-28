#pragma once
#include "DataTable.h"
#include <Zombie.h>

enum class TYPE
{
	NONE,
	HP = 1,
	MOVE_SPEED = 2,
	ATTACK_DAMAGE = 3,
};

struct DataLevelUp 
{
	int id;

	std::wstring name;
	std::wstring desc;
	std::string textureId;

	TYPE type;

	float value;
	int weight;
};

class LevelUpTable : public DataTable
{
protected:
	std::unordered_map<int, DataLevelUp> table;

public:
	LevelUpTable(DataTable::Types t);
	~LevelUpTable() override;

	bool Load() override;
	void Release() override;

	const DataLevelUp& Get();

	std::wstring CP949ToWString(const std::string& str);
	
};

