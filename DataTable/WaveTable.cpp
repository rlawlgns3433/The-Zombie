#include "pch.h"
#include "WaveTable.h"
#include "rapidcsv.h"

DATA_WAVE WaveTable::unDef = {};


WaveTable::WaveTable(DataTable::Types t)
	:DataTable(t)
{
}

WaveTable::~WaveTable()
{
	Release();
}


bool WaveTable::Load()
{
	Release();

	rapidcsv::Document doc("data/WaveTable.csv");
	lastWave = doc.GetRowCount();
	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		auto row = doc.GetRow<std::string>(i);
		int id = std::stoi(row[0]);

		if (table.find(id) != table.end())
		{
			std::cout << "웨이브 테이블 중복 아이디 발견!" << std::endl;
			return false;
		}

		table[id] = DATA_WAVE();
		table[id].descriptionId = Utils::CP949ToWString(row[1]);

		table[id].tileX = std::stoi(row[2]);
		table[id].tileY = std::stoi(row[3]);

		table[id].zombieCount = std::stoi(row[4]);
		table[id].itemAmount = std::stoi(row[5]);
		table[id].zombieAmount = std::stoi(row[6]);

		table[id].zombie0W = std::stoi(row[7]);
		table[id].zombie1W = std::stoi(row[8]);
		table[id].zombie2W = std::stoi(row[9]);

	}

	return true;
}

void WaveTable::Release()
{
	table.clear();
}

const DATA_WAVE& WaveTable::Get(int id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		std::cout << "웨이브 테이블 없";
		return unDef;

	}
	return find->second;

}