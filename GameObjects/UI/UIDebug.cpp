#include "pch.h"
#include "UIDebug.h"

UIDebug::UIDebug(const std::string& name)
	:GameObject(name)
{
}

void UIDebug::Init()
{
	GameObject::Init();

	fps.setFont(RES_MGR_FONT.Get("fonts/zombiecontrol.ttf"));
	fps.setCharacterSize(20);
	fps.setPosition(0, textY);
	fps.setFillColor(sf::Color::Green);

	textY += 20;
	for (auto text : debugTextList)
	{
		text->setFont(RES_MGR_FONT.Get("fonts/zombiecontrol.ttf"));
		text->setCharacterSize(20);
		text->setPosition(0, textY);
		text->setFillColor(sf::Color::Red);
		textY += 20;
	}

	textBG.setPosition(0, textY - 20);
	textBG.setFillColor(sf::Color(0, 0, 0, 80));
	textBG.setSize({ 100, textY - 180 });
}

void UIDebug::Release()
{
	for (auto ptr : debugTextList)
	{
		delete ptr;
	}
}

void UIDebug::Reset()
{
	debugTextList.clear();
	textY = 200;
}

void UIDebug::DebugUpdate(float dt)
{
	fps.setString(std::to_string(1.f / dt));
	textX = std::max(textX, fps.getGlobalBounds().width);
	for (auto text : debugTextList)
	{
		textX = std::max(textX, text->getGlobalBounds().width);
	}
	textBG.setSize({ textX,textY - 200 });
}

void UIDebug::ListUpdate()
{
	while (!textRemoveList.empty())
	{
		debugTextList.remove(textRemoveList.front());
		textRemoveList.pop_front();
		textY -= 20;
	}
}

void UIDebug::DebugDraw(sf::RenderWindow& window)
{
	window.draw(textBG);
	window.draw(fps);
	for (auto ptr : debugTextList)
	{
		window.draw(*ptr);
	}
}

sf::Text* UIDebug::AddText(sf::Text* text)
{
	debugTextList.push_back(text);
	text->setFont(RES_MGR_FONT.Get("fonts/zombiecontrol.ttf"));
	text->setCharacterSize(20);
	text->setPosition(0, textY);
	text->setFillColor(sf::Color::Red);
	textY += 20;
	return text;
}

void UIDebug::RemoveText(sf::Text* text)
{
	textRemoveList.push_back(text);
}
