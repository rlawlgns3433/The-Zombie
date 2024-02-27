#include "pch.h"
#include "UILevelUp.h"
#include "SpriteGo.h"
#include "TextGo.h"

UILevelUp::UILevelUp(const std::string& name)
{

}

UILevelUp::~UILevelUp()
{
	UiDelete();
}

void UILevelUp::Init()
{
	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");
	NewTextGo("Hello", font, "Hi", 55, sf::Color::White);
	texts["Hello"]->SetPosition({ 0,0 });

	UiInit();
}

void UILevelUp::Release()
{
	GameObject::Release();

	UiDelete();
}

void UILevelUp::Reset()
{
	GameObject::Reset();
}

void UILevelUp::Update(float dt)
{
	GameObject::Update(dt);
}

void UILevelUp::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}

void UILevelUp::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);

	UiDraw(window);
}

void UILevelUp::NewSpriteGo(const std::string& name, 
	const std::string& textureId)
{
	sprites.insert( { name, new SpriteGo(name) } );
	sprites[name]->SetTexture(textureId);
}

void UILevelUp::NewTextGo(const std::string& name, 
	const sf::Font& font, const std::string& str, 
	int size, const sf::Color& color)
{
	texts.insert( { name , new TextGo(name) } );

	texts[name]->Set(font, str, size, color);
}

void UILevelUp::UiInit()
{
	for (auto data : sprites)
	{
		data.second->Init();
	}

	for (auto data : texts)
	{
		data.second->Init();
	}
}

void UILevelUp::UiDraw(sf::RenderWindow& window)
{
	for (auto data : sprites)
	{
		data.second->Draw(window);
	}

	for (auto data : texts)
	{
		data.second->Draw(window);
	}
}

void UILevelUp::UiDelete()
{
	for (auto data : sprites)
	{
		delete data.second;
	}

	for (auto data : texts)
	{
		delete data.second;
	}
}
