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
	// **����** ���α׷��� ����ɶ� UIDebug�� ������ �ִ� Text�� delete��.
	void Reset() override;
	void DebugUpdate(float dt) override;
	void DebugDraw(sf::RenderWindow& window) override;

	// **����** ���α׷��� ����Ǳ� ������ delete���� ����.
	sf::Text* AddText(sf::Text* text);
	// **����** delete���� ����.
	void RemoveText(sf::Text* text);

	inline static UIDebug& Instance()
	{
		static UIDebug instance;
		return instance;
	}
};

#define UI_DEBUG (UIDebug::Instance())