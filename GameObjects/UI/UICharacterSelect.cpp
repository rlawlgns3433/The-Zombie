#include "pch.h"
#include "UICharacterSelect.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Crosshair.h"
#include "DataTableMgr.h"
#include "CharacterSelectTable.h"

UICharacterSelect::UICharacterSelect(const std::string& name)
	: GameObject(name)
{
	Init();
}

UICharacterSelect::~UICharacterSelect()
{
	UiDelete();
}

void UICharacterSelect::Init()
{
	mouse = FRAMEWORK.GetMouse();

	sf::Font& font = RES_MGR_FONT.Get("fonts/BMHANNAPro.ttf");

	characterTable.push_back(DT_CHARACTER_SELECT->Get(Player::TYPES::MAN));
	characterTable.push_back(DT_CHARACTER_SELECT->Get(Player::TYPES::FIREBAT));
	characterTable.push_back(DT_CHARACTER_SELECT->Get(Player::TYPES::READDEATH));
	characterTable.push_back(DT_CHARACTER_SELECT->Get(Player::TYPES::TIMBER));

	//************************캐릭터 선택 UI***********************
	NewSpriteGo("CharacterSelect", "graphics/characterSelect.PNG");
	sprites["CharacterSelect"]->SetOrigin(Origins::MC);
	sprites["CharacterSelect"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f , FRAMEWORK.GetWindowSize().y * 0.5f, });
	sprites["CharacterSelect"]->SetScale({ 1.5f , 1.5f });

	//************************캐릭터 이미지************************
	NewSpriteGo("Character1Img", characterTable[0].textureId);
	NewSpriteGo("Character2Img", characterTable[1].textureId);
	NewSpriteGo("Character3Img", characterTable[2].textureId);
	NewSpriteGo("Character4Img", characterTable[3].textureId);

	sprites["Character1Img"]->SetPosition({ FRAMEWORK.GetWindowSize().x
		* 0.3f , FRAMEWORK.GetWindowSize().y * 0.18f, });
	sprites["Character1Img"]->SetScale({ 3.f , 3.f });

	sprites["Character2Img"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.415f , FRAMEWORK.GetWindowSize().y * 0.2f, });
	sprites["Character2Img"]->SetScale({ 3.5f , 3.5f });

	sprites["Character3Img"]->SetPosition({ 470 , 500 });
	sprites["Character3Img"]->SetScale({ 1.5f , 1.5f });

	sprites["Character4Img"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.62f , FRAMEWORK.GetWindowSize().y * 0.2f, });
	sprites["Character4Img"]->SetScale({ 0.6f , 0.6f });

	//************************캐릭터 텍스트************************
	NewTextGo("Character1Name", font, characterTable[0].nameId, 30, sf::Color::White);
	texts["Character1Name"]->SetPosition({ 590, 180 });

	NewTextGo("Character2Name", font, characterTable[1].nameId, 30, sf::Color::White);
	texts["Character2Name"]->SetPosition({ 785, 180 });

	NewTextGo("Character3Name", font, characterTable[2].nameId, 30, sf::Color::White);
	texts["Character3Name"]->SetPosition({ 980, 180 });

	NewTextGo("Character4Name", font, characterTable[3].nameId, 30, sf::Color::White);
	texts["Character4Name"]->SetPosition({ 1175, 180 });

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

	//std::cout << mouse->GetPosition().x << " " <<
	//	mouse->GetPosition().y << std::endl;
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

