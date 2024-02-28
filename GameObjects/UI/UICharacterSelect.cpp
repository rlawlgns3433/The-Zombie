#include "pch.h"
#include "UICharacterSelect.h"
#include "SpriteGo.h"
#include "TextGo.h"

UICharacterSelect::UICharacterSelect(const std::string& name)
	: GameObject(name)
{}

UICharacterSelect::~UICharacterSelect()
{
	UiDelete();
}

void UICharacterSelect::Init()
{
	UiInit();
}

void UICharacterSelect::Release()
{
	GameObject::Release();

	UiDelete();
}

void UICharacterSelect::Reset()
{
	GameObject::Reset();
}

void UICharacterSelect::Update(float dt)
{
	GameObject::Update(dt);
}

void UICharacterSelect::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}

void UICharacterSelect::Draw(sf::RenderWindow & window)
{
	GameObject::Draw(window);

	UiDraw(window);
}

void UICharacterSelect::NewSpriteGo(const std::string & name, const std::string & textureId)
{
	sprites.insert({ name, new SpriteGo(name) });
	sprites[name]->SetTexture(textureId);
}

void UICharacterSelect::NewTextGo(const std::string & name, const sf::Font & font, const std::wstring & str, int size, const sf::Color & color)
{
	texts.insert({ name , new TextGo(name) });
	texts[name]->Set(font, str, size, color);
}

void UICharacterSelect::UiInit()
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

void UICharacterSelect::UiDraw(sf::RenderWindow & window)
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

void UICharacterSelect::UiDelete()
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

