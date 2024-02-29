#pragma once
class DataTable
{

public:
	enum class Types
	{
		String,
		Zombie,
		LevelUp,
		PLAYER,
		ITEM,
		PLAYER_SELECT,
		WAVE
	};
	static const int TotalTypes = 6;

private:
	Types type;
public:

	inline DataTable(Types t) :type(t) {};
	virtual ~DataTable() = default;

	virtual bool Load() = 0;
	virtual void Release() = 0;




};

