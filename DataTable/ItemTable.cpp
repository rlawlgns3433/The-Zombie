#include "pch.h"
#include "ItemTable.h"
#include "rapidcsv.h"

DATA_ITEM ItemTable::Undefined = DATA_ITEM();

ItemTable::ItemTable(DataTable::Types type)
    : DataTable(type)
{
}

ItemTable::~ItemTable()
{
    Release();
}

bool ItemTable::Load()
{
    Release();
    rapidcsv::Document doc("data/ItemTable.csv");
	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		auto row = doc.GetRow<std::string>(i);
		Item::Types id = (Item::Types)std::stoi(row[0]);

		if (table.find(id) != table.end())
		{
			std::cout << "아이템 테이블 중복!" << std::endl;
			return false;
		}

		table[id] = DATA_ITEM();
		table[id].id = id;
		table[id].nameId = row[1];
		table[id].descriptionId = row[2];
		table[id].textureId = row[3];
		table[id].minVal = std::stoi(row[4]);
		table[id].maxVal = std::stof(row[5]);
	}

    return false;
}

void ItemTable::Release()
{
	table.clear();
}

const DATA_ITEM& ItemTable::Get(Item::Types id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		std::cout << "테이블에서 찾을 수 없습니다." << std::endl;
		return Undefined;
	}

	return find->second;
}
