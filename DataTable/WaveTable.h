#pragma once
#include "DataTable.h"
struct DATA_WAVE
{
	int id;
	std::wstring descriptionId;

	int tileX;
	int tileY;

	int zombieCount;
	int itemAmount;
	int zombieAmount;


	int zombie0W; //�������̺� 0���� ����ġ
	int zombie1W; //�������̺� 1���� ����ġ
	int zombie2W; 

};


class WaveTable : public DataTable
{
	static DATA_WAVE unDef;
protected:
	std::unordered_map<int, DATA_WAVE> table;
	int lastWave = 0;

public:
	WaveTable(DataTable::Types t);
	~WaveTable() override;

	bool Load() override;
	void Release() override;

	const DATA_WAVE& Get(int id);
	inline int GetLastWave() const { return lastWave; }
};

