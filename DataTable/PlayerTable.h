#pragma once
#include "DataTable.h"
#include "Player.h"

struct DATA_PLAYER
{
	Player::TYPES id;

	std::string nameId;
	std::string descriptionId;
	std::string textureId;

	int maxHp;
	float speed;
};


class PlayerTable : public DataTable
{
	static DATA_PLAYER unDef;
protected:
	std::unordered_map<Player::TYPES, DATA_PLAYER> table;

public:
	PlayerTable(DataTable::Types t);
	~PlayerTable() override;

	bool Load() override;
	void Release() override;

	const DATA_PLAYER& Get(Player::TYPES id);
};

