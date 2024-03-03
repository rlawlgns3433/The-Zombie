#pragma once

#include "UIGo.h"
#include "LevelUpTable.h"

class SpriteGo;
class TextGo;
class Crosshair;

struct SelectBox
{
	std::string name;
	sf::FloatRect bounds;
};

class UILevelUp : public UIGo
{
protected:

	std::vector<SelectBox> selectBoxs;
	std::vector<DataLevelUp> currentDataLevelUp;
	DataLevelUp playerDataLevelUp;

public:
	UILevelUp(const std::string& name = "");
	~UILevelUp() override;
	UILevelUp(const UILevelUp&) = delete;
	UILevelUp(UILevelUp&&) = delete;
	UILevelUp& operator=(const UILevelUp&) = delete;
	UILevelUp& operator=(UILevelUp&&) = delete;


	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void LevelUp();

	void HandleMouseSelection();
	void ProcessSelection(std::string& name);

	DataLevelUp PlayerLevelUp();
};

