#pragma once
#include "GameObject.h"

class UIDebug final : public GameObject
{
private:
	std::list<sf::Text*> debugTextList;
	sf::Text fps;
	float textX = 0;
	float textY = 200;
	sf::RectangleShape textBG;

	UIDebug(const std::string& name = "Debug");
	UIDebug(UIDebug&&) = delete;
	UIDebug(const UIDebug&) = delete;
public:	

	~UIDebug() override = default;
	UIDebug& operator=(const UIDebug&) = delete;
	UIDebug& operator=(UIDebug&&) = delete;


	void Init() override;
	void Release() override;
	// **주의** 프로그램이 종료될때 UIDebug가 가지고 있는 Text만 delete함.
	void Reset() override;
	void DebugUpdate(float dt) override;
	void DebugDraw(sf::RenderWindow& window) override;

	// **주의** 프로그램이 종료되기 전까지 delete하지 않음.
	sf::Text* AddText(sf::Text* text);
	// **주의** delete하지 않음.
	void RemoveText(sf::Text* text);

	inline static UIDebug& Instance()
	{
		static UIDebug instance;
		return instance;
	}
};

#define UI_DEBUG (UIDebug::Instance())