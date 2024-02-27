#pragma once
class DataTable
{

public:
	enum class Types
	{
		String,
		Int,

	};
	static const int TotalTypes = 1;

private:
	Types type;
public:

	inline DataTable(Types t) :type(t) {};
	virtual ~DataTable() = default;

	virtual bool Load() = 0;
	virtual void Release() = 0;




};

