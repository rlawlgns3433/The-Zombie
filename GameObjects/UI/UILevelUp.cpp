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
	sf::Font& font = RES_MGR_FONT.Get("fonts/BMHANNAPro.ttf");

	//************************������ ��� UI***********************
	NewSpriteGo("LevelUp", "graphics/levelup.png");
	sprites["LevelUp"]->SetOrigin(Origins::MC);
	sprites["LevelUp"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f , FRAMEWORK.GetWindowSize().y * 0.5f, });
	sprites["LevelUp"]->SetScale({ 0.8f , 0.8f });
	sprites["LevelUp"]->sortLayer = 3;

	//************************1��° ���� UI************************
	NewTextGo("Selete1Name", font, L"�尩", 35, sf::Color::White);
	texts["Selete1Name"]->SetPosition({ 730, 260 });
	NewTextGo("Selete1Desc", font, L"�� �尩�� �÷��̾�� HP50 ���������� �����մϴ�.", 25, sf::Color::White);
	texts["Selete1Desc"]->SetPosition({ 660, 350 });
	NewSpriteGo("Selete1Img", "graphics/heart.png");
	sprites["Selete1Img"]->sortLayer = 5;
	sprites["Selete1Img"]->SetPosition({ 647, 263 });
	sprites["Selete1Img"]->SetScale({ 0.6f , 0.6f });

	//************************2��° ���� UI************************
	NewTextGo("Selete2Name", font, L"����", 35, sf::Color::White);
	texts["Selete2Name"]->SetPosition({ 730, 430 });
	NewTextGo("Selete2Desc", font, L"�� ����� �÷��̾�� ���ݷ��� 50 ���������� �����մϴ�.", 25, sf::Color::White);
	texts["Selete2Desc"]->SetPosition({ 660, 520 });
	NewSpriteGo("Selete2Img", "graphics/cape.png");
	sprites["Selete2Img"]->sortLayer = 5;
	sprites["Selete2Img"]->SetPosition({ 647, 431 });
	sprites["Selete2Img"]->SetScale({ 0.6f , 0.6f });

	//************************3��° ���� UI************************
	NewTextGo("Selete3Name", font, L"������ �Ź�", 35, sf::Color::White);
	texts["Selete3Name"]->SetPosition({ 730, 600 });
	NewTextGo("Selete3Desc", font, L"�� �Ź��� �÷��̾�� �̵��ӵ� 50 ���������� �����մϴ�.", 25, sf::Color::White);
	texts["Selete3Desc"]->SetPosition({ 660, 690 });
	NewSpriteGo("Selete3Img", "graphics/shose.png");
	sprites["Selete3Img"]->sortLayer = 5;
	sprites["Selete3Img"]->SetPosition({ 647, 598 });
	sprites["Selete3Img"]->SetScale({ 0.6f , 0.6f });

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

void UILevelUp::LevelUp()
{

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
	const sf::Font& font, const std::wstring& str,
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
