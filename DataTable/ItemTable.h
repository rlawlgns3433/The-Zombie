#pragma once
#include "DataTable.h"
#include "Item.h"

struct DATA_ITEM
{
	Item::Types id;

	std::string nameId;
	std::string descriptionId;
	std::string textureId;

	int minVal;
	int maxVal;

};


class ItemTable : public DataTable
{
public :
	static DATA_ITEM Undefined;

protected :
	std::unordered_map<Item::Types, DATA_ITEM> table;

public :
	ItemTable(DataTable::Types type);
	~ItemTable() override;
	ItemTable(const ItemTable&) = delete;
	ItemTable(ItemTable&&) = delete;
	ItemTable& operator=(const ItemTable&) = delete;
	ItemTable& operator=(ItemTable&&) = delete;

	bool Load() override;
	void Release() override;

	const DATA_ITEM& Get(Item::Types id);
};