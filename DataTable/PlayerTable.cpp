#include "pch.h"
#include "PlayerTable.h"
#include "rapidcsv.h"

DATA_PLAYER PlayerTable::unDef = {};


PlayerTable::PlayerTable(DataTable::Types t)
	:DataTable(t)
{
}

PlayerTable::~PlayerTable()
{
	Release();
}


bool PlayerTable::Load()
{
	Release();

	rapidcsv::Document doc("data/PlayerTable.csv");
	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		auto row = doc.GetRow<std::string>(i);
		Player::TYPES id = (Player::TYPES)std::stoi(row[0]);

		if (table.find(id) != table.end())
		{
			std::cout << "플레이어 테이블 중복 아이디 발견!" << std::endl;
			return false;
		}

		table[id] = DATA_PLAYER();
		table[id].id = id;
		table[id].nameId = row[1];
		table[id].descriptionId = row[2];
		table[id].textureId = row[3];
		table[id].maxHp = std::stoi(row[4]);
		table[id].speed = std::stof(row[5]);

	}

	return true;
}

void PlayerTable::Release()
{
	table.clear();
}

const DATA_PLAYER& PlayerTable::Get(Player::TYPES id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		std::cout << "플레이어 테이블 없";
		return unDef;

	}
	return find->second;

}