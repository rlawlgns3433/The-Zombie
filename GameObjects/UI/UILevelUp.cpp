#include "pch.h"
#include "UILevelUp.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "DataTableMgr.h"
#include "LevelUpTable.h"
#include "Framework.h"
#include "Crosshair.h"
#include "UIGo.h"

UILevelUp::UILevelUp(const std::string& name) : UIGo(name)
{

}

UILevelUp::~UILevelUp()
{
	
}

void UILevelUp::Init()
{

	sf::Font& font = RES_MGR_FONT.Get("fonts/BMHANNAPro.ttf");

	//************************레벨업 배경 UI***********************
	NewSpriteGo("LevelUp", "graphics/levelup.png");
	sprites["LevelUp"]->SetOrigin(Origins::MC);
	sprites["LevelUp"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f , FRAMEWORK.GetWindowSize().y * 0.5f, });
	sprites["LevelUp"]->SetScale({ 0.8f , 0.8f });

	//************************1번째 선택 UI************************
	NewTextGo("Selete1Name", font, L"", 35, sf::Color::White);
	texts["Selete1Name"]->SetPosition({ 730, 260 });
	NewTextGo("Selete1Desc", font, L"", 25, sf::Color::White);
	texts["Selete1Desc"]->SetPosition({ 660, 333 });
	NewSpriteGo("Selete1Img", "graphics/stat/potion1.png");
	sprites["Selete1Img"]->SetPosition({ 647, 263 });
	sprites["Selete1Img"]->SetScale({ 0.6f , 0.6f });

	//************************2번째 선택 UI************************
	NewTextGo("Selete2Name", font, L"", 35, sf::Color::White);
	texts["Selete2Name"]->SetPosition({ 730, 430 });
	NewTextGo("Selete2Desc", font, L"", 25, sf::Color::White);
	texts["Selete2Desc"]->SetPosition({ 660, 500 });
	NewSpriteGo("Selete2Img", "graphics/stat/potion1.png");
	sprites["Selete2Img"]->SetPosition({ 647, 431 });
	sprites["Selete2Img"]->SetScale({ 0.6f , 0.6f });

	//************************3번째 선택 UI************************
	NewTextGo("Selete3Name", font, L"", 35, sf::Color::White);
	texts["Selete3Name"]->SetPosition({ 730, 600 });
	NewTextGo("Selete3Desc", font, L"", 25, sf::Color::White);
	texts["Selete3Desc"]->SetPosition({ 660, 670 });
	NewSpriteGo("Selete3Img", "graphics/stat/potion1.png");
	sprites["Selete3Img"]->SetPosition({ 647, 598 });
	sprites["Selete3Img"]->SetScale({ 0.6f , 0.6f });



	SelectBox box1 = { "graphics/levelup_selete1.png" , 
		sf::FloatRect({640 , 250, 640 ,160}) };

	SelectBox box2 = { "graphics/levelup_selete2.png" , 
		sf::FloatRect({640 , 420, 640 ,160}) };

	SelectBox box3 = { "graphics/levelup_selete3.png" , 
		sf::FloatRect({640 , 590, 640 ,160}) };

	selectBoxs.push_back(box1);
	selectBoxs.push_back(box2);
	selectBoxs.push_back(box3);

	UiInit();
	ObjectsSort();

	SetActive(false);
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

	//std::cout << mouse->GetPosition().x << " ";
	//std::cout << mouse->GetPosition().y << std::endl;

	HandleMouseSelection();
}

void UILevelUp::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}

void UILevelUp::LevelUp()
{
	currentDataLevelUp.clear();

	SOUND_MGR.PlaySfx("sound/ui/jump09.wav");
	for (int i = 1; i < 4; i++)
	{
		DataLevelUp dlu = DT_LEVELUP->Get();

		currentDataLevelUp.push_back(dlu);

		texts["Selete" + std::to_string(i) + "Name"]->
			SetString(dlu.name);
		texts["Selete" + std::to_string(i) + "Desc"]->
			SetString(dlu.desc+L"\n"+dlu.effect);
		sprites["Selete" + std::to_string(i) + "Img"]->
			SetTexture(dlu.textureId);
	}

	SetActive(true);
}

void UILevelUp::HandleMouseSelection()
{
	for (int i = 0; i < 3; i++)
	{
		if (selectBoxs[i].bounds.contains(mouse->GetPosition()))
		{
			ProcessSelection(selectBoxs[i].name);

			if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
			{
				playerDataLevelUp = currentDataLevelUp[i];
				SOUND_MGR.PlaySfx("sound/ui/powerup02.wav");
				SetActive(false);
			}
			break;
		}
		else
		{
			sprites["LevelUp"]->SetTexture("graphics/levelup.png");
		}
	}
}

void UILevelUp::ProcessSelection(std::string& name)
{
	sprites["LevelUp"]->SetTexture(name);
}

DataLevelUp UILevelUp::PlayerLevelUp()
{
	return playerDataLevelUp;
}

