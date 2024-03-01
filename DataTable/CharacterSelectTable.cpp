#include "pch.h"
#include "CharacterSelectTable.h"
#include "rapidcsv.h"

DATA_PLAYER_SELECT CharacterSelectTable::unDef = {};

CharacterSelectTable::CharacterSelectTable(DataTable::Types t)
	: DataTable(t)
{

}

CharacterSelectTable::~CharacterSelectTable()
{
	Release();
}

bool CharacterSelectTable::Load()
{
	rapidcsv::Document doc("data/CharacterSelectTable.csv");

	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		auto row = doc.GetRow<std::string>(i);

		Player::TYPES id = (Player::TYPES)std::stoi(row[0]);

		if (table.find(id) != table.end())
		{
			std::cout << "캐릭터 선택 테이블 중복 아이디 발견!" << std::endl;
			return false;
		}
		
		table[id] = DATA_PLAYER_SELECT();

		table[id].id = id;
		table[id].nameId = Utils::CP949ToWString(row[1]);
		table[id].descId = Utils::CP949ToWString(row[2]);
		table[id].textureId = row[3];
	}

	return true;
}

void CharacterSelectTable::Release()
{
	table.clear();
}

const DATA_PLAYER_SELECT& CharacterSelectTable::Get(Player::TYPES id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		std::cout << "테이블 없음";
		return unDef;
	}
	return find->second;
}
