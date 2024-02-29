#pragma once

class SpriteGo;
class TextGo;
class DATA_PLAYER_SELECT;

class UICharacterSelect : public GameObject
{
protected:
	std::map<std::string, SpriteGo*> sprites;
	std::unordered_map<std::string, TextGo*> texts;

	std::vector<DATA_PLAYER_SELECT> characterTable;
	std::vector<SpriteGo*> sortSprites;

	// 충돌 처리 컨테이너
	std::vector<SpriteGo*> selectBoxs;
	std::vector<SpriteGo*> checkBoxs;

	Crosshair* mouse = nullptr;

	bool check = false;

	int playerIndex = 0;

public:
	UICharacterSelect(const std::string& name = "");
	~UICharacterSelect() override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;
	void SetCheck(bool c);

	void NewSpriteGo(const std::string& name,
		const std::string& textureId);
	void NewTextGo(const std::string& name,
		const sf::Font& font, const std::wstring& str,
		int size, const sf::Color& color);

	void UiInit();
	void UiDraw(sf::RenderWindow& window);
	void UiDelete();

	void HandleMouseSelection();
	void HandleCheckMouseSelection();

	static bool compareSpriteGoBySortLayer(SpriteGo* a,
		SpriteGo* b);
};

