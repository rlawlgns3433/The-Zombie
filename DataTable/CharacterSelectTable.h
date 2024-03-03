#pragma once
#include "DataTable.h"
#include "Player.h"

struct DATA_PLAYER_SELECT
{
	Player::TYPES id;

	std::wstring nameId;
	std::wstring descId;

	std::string textureId;
};

class CharacterSelectTable : public DataTable
{
	static DATA_PLAYER_SELECT unDef;

protected:
	std::unordered_map<Player::TYPES, DATA_PLAYER_SELECT> table;

public:
	CharacterSelectTable(DataTable::Types t);
	~CharacterSelectTable() override;
	CharacterSelectTable(const CharacterSelectTable&) = delete;
	CharacterSelectTable(CharacterSelectTable&&) = delete;
	CharacterSelectTable& operator=(const CharacterSelectTable&) = delete;
	CharacterSelectTable& operator=(CharacterSelectTable&&) = delete;

	bool Load() override;
	void Release() override;

	const DATA_PLAYER_SELECT& Get(Player::TYPES id);
};

