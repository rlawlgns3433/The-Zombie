#pragma once
#include "UIGo.h"

class SpriteGo;
class TextGo;
class DATA_PLAYER_SELECT;

class UICharacterSelect : public UIGo
{
protected:
	std::vector<DATA_PLAYER_SELECT> characterTable;

	// 충돌 처리 컨테이너
	std::vector<SpriteGo*> selectBoxs;
	std::vector<SpriteGo*> checkBoxs;

	bool check = false;

	int playerIndex = 0;

public:
	UICharacterSelect(const std::string& name = "");
	~UICharacterSelect() override;
	UICharacterSelect(const UICharacterSelect&) = delete;
	UICharacterSelect(UICharacterSelect&&) = delete;
	UICharacterSelect& operator=(const UICharacterSelect&) = delete;
	UICharacterSelect& operator=(UICharacterSelect&&) = delete;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void SetCheck(bool c);

	void HandleMouseSelection();
};

