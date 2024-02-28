#include "pch.h"
#include "LevelUpTable.h"
#include "rapidcsv.h"

LevelUpTable::LevelUpTable(DataTable::Types t)
	: DataTable(t)
{
}

LevelUpTable::~LevelUpTable()
{
}

bool LevelUpTable::Load()
{
	Release();

	rapidcsv::Document doc("data/LevelUpTable.csv");

	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		auto row = doc.GetRow<std::string>(i);

		table[i] = DataLevelUp();
		table[i].id = std::stoi(row[0]);
		table[i].name = Utils::CP949ToWString(row[1]);
		table[i].desc = Utils::CP949ToWString(row[2]);
		table[i].effect = Utils::CP949ToWString(row[3]);
		table[i].textureId = row[4];

		table[i].weight = std::stoi(row[5]);

		table[i].maxHp = std::stoi(row[6]);
		table[i].speed = std::stof(row[7]);
		table[i].xExp = std::stof(row[8]);
		table[i].damage = std::stoi(row[9]);
		table[i].shotInterval = std::stof(row[10]);
		table[i].reloadInterval = std::stof(row[11]);
		table[i].maxAmmo = std::stoi(row[12]);
		table[i].weaponUp = std::stoi(row[13]);

	}

	return true;
}

void LevelUpTable::Release()
{
	table.clear();
}

const DataLevelUp& LevelUpTable::Get()
{
	int randomIndex = Utils::RandomRange(0, table.size());

	return table[randomIndex];
}                                                                                                                                             

