#pragma once
#include "Singleton.h"
#include "DataTable.h"

class DataTableMgr : public Singleton<DataTableMgr>
{
	friend Singleton<DataTableMgr>;
private:
	DataTableMgr();
	~DataTableMgr();
	DataTableMgr(const DataTableMgr&) = delete;
	DataTableMgr(DataTableMgr&&) = delete;
	DataTableMgr& operator=(const DataTableMgr&) = delete;
	DataTableMgr& operator=(DataTableMgr&&) = delete;

	std::unordered_map<DataTable::Types, DataTable*> tables;

public:
	void Init();
	void Release();

	template<typename T>
	T* Get(DataTable::Types type);


};

template<typename T>
inline T* DataTableMgr::Get(DataTable::Types type)
{

	auto find = tables.find(type);
	if (find == tables.end())
	{
		return nullptr;
	}

	return dynamic_cast<T*>(find->second);
}

#define DT_MGR (DataTableMgr::Instance())
#define DT_STRING (DT_MGR.Get<StringTable>(DataTable::Types::String))
#define DT_ZOMBIE (DT_MGR.Get<ZombieTable>(DataTable::Types::Zombie))
#define DT_LEVELUP (DT_MGR.Get<LevelUpTable>(DataTable::Types::LevelUp))
#define DT_PLAYER (DT_MGR.Get<PlayerTable>(DataTable::Types::PLAYER))
#define DT_ITEM (DT_MGR.Get<ItemTable>(DataTable::Types::ITEM))
#define DT_CHARACTER_SELECT (DT_MGR.Get<CharacterSelectTable>(DataTable::Types::PLAYER_SELECT))
#define DT_WAVE (DT_MGR.Get<WaveTable>(DataTable::Types::WAVE))
