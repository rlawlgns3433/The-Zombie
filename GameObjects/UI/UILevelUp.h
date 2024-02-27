#pragma once
#include "GameObject.h"

class SpriteGo;
class TextGo;

class UILevelUp : public GameObject
{
protected:
	std::unordered_map<std::string, SpriteGo*> sprites;
	std::unordered_map<std::string, TextGo*> texts;

public:
	UILevelUp(const std::string& name);
	~UILevelUp() override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void LevelUp();

	void Draw(sf::RenderWindow& window) override;

	void NewSpriteGo(const std::string& name, 
		const std::string& textureId);
	void NewTextGo(const std::string& name,
		const sf::Font& font, const std::wstring& str,
		int size, const sf::Color& color);


	void UiInit();
	void UiDraw(sf::RenderWindow& window);
	void UiDelete();
};

