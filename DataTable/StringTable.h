#pragma once
#include "DataTable.h"
class StringTable : public DataTable
{

	static std::string unDef;
protected:
	std::unordered_map<std::string, std::string> table;
	Languages currLang = Languages::Korean;

public:
	StringTable(Types t);
	~StringTable() override;
	StringTable(const StringTable&) = delete;
	StringTable(StringTable&&) = delete;
	StringTable& operator=(const StringTable&) = delete;
	StringTable& operator=(StringTable&&) = delete;

	bool Load() override;
	bool Load(Languages lang);

	void Release() override;

	const std::string& Get(const std::string& id);
};

