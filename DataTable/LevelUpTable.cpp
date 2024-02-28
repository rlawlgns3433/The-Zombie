#include "pch.h"
#include "LevelUpTable.h"
#include "rapidcsv.h"
#include <string>
#include <windows.h>

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
		table[i].name = CP949ToWString(row[1]);
		table[i].desc = CP949ToWString(row[2]);
		table[i].textureId = row[3];
		table[i].type = (TYPE)std::stoi(row[4]);
		table[i].value = std::stof(row[5]);
		table[i].weight = std::stoi(row[6]);
	}

	return true;
}

void LevelUpTable::Release()
{
	table.clear();
}

std::wstring LevelUpTable::CP949ToWString(const std::string& str)
{
	if (str.empty()) return L"";
	// CP949 코드 페이지를 사용하여 변환
	int sizeNeeded = MultiByteToWideChar(949, 0, str.c_str(), (int)str.size(), NULL, 0);
	std::wstring wstrTo(sizeNeeded, 0);
	MultiByteToWideChar(949, 0, str.c_str(), (int)str.size(), &wstrTo[0], sizeNeeded);
	return wstrTo;
}

const DataLevelUp& LevelUpTable::Get()
{
	int randomIndex = Utils::RandomRange(0, table.size());

	return table[randomIndex];
}                                                                                                                                             

