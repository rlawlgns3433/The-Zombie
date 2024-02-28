#include "pch.h"
#include "DataTableMgr.h"
#include "StringTable.h"
#include "ZombieTable.h"
#include "LevelUpTable.h"
#include "PlayerTable.h"

DataTableMgr::DataTableMgr()
{
}

DataTableMgr::~DataTableMgr()
{
	Release();
}

void DataTableMgr::Init()
{
	Release();

	//StringTable
	DataTable* stringTable = new StringTable(DataTable::Types::String);
	stringTable->Load();
	tables.insert({ DataTable::Types::String, stringTable });

	//ZombieTable
	DataTable* zombieTable = new ZombieTable(DataTable::Types::Zombie);
	zombieTable->Load();
	tables.insert({ DataTable::Types::Zombie, zombieTable });

	//LevelUpTable
	LevelUpTable* levelUpTable = new LevelUpTable(DataTable::Types::LevelUp);
	levelUpTable->Load();
	tables.insert({ DataTable::Types::LevelUp, levelUpTable });

	//PlayerTable
	PlayerTable* playerTable = new PlayerTable(DataTable::Types::PLAYER);
	playerTable->Load();
	tables.insert({ DataTable::Types::PLAYER, playerTable });

}

void DataTableMgr::Release()
{
	for (auto pair : tables)
	{
		delete pair.second;
	}
	tables.clear();
}