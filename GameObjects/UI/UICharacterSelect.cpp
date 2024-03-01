#include "pch.h"
#include "UICharacterSelect.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Crosshair.h"
#include "DataTableMgr.h"
#include "CharacterSelectTable.h"
#include "UIGo.h"

UICharacterSelect::UICharacterSelect(const std::string& name)
	: UIGo(name)
{
	Init();
}

UICharacterSelect::~UICharacterSelect()
{
	
}

void UICharacterSelect::Init()
{
	sf::Font& font = RES_MGR_FONT.Get("fonts/BMHANNAPro.ttf");

	characterTable.push_back(DT_CHARACTER_SELECT->Get(Player::TYPES::MAN));
	characterTable.push_back(DT_CHARACTER_SELECT->Get(Player::TYPES::FIREBAT));
	characterTable.push_back(DT_CHARACTER_SELECT->Get(Player::TYPES::READDEATH));
	characterTable.push_back(DT_CHARACTER_SELECT->Get(Player::TYPES::TIMBER));

	//************************캐릭터 선택 UI***********************
	NewSpriteGo("CharacterSelect", "graphics/characterselect.PNG");
	sprites["CharacterSelect"]->SetOrigin(Origins::MC);
	sprites["CharacterSelect"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f , FRAMEWORK.GetWindowSize().y * 0.5f, });
	sprites["CharacterSelect"]->SetScale({ 1.5f , 1.5f });
	sprites["CharacterSelect"]->sortLayer = 5;

	//************************캐릭터 박스 UI***********************
	NewSpriteGo("Characterbox1", "graphics/character_select_box.PNG");
	NewSpriteGo("Characterbox2", "graphics/character_select_box.PNG");
	NewSpriteGo("Characterbox3", "graphics/character_select_box.PNG");
	NewSpriteGo("Characterbox4", "graphics/character_select_box.PNG");

	sprites["Characterbox1"]->SetScale({ 1.5f , 1.5f });
	sprites["Characterbox2"]->SetScale({ 1.5f , 1.5f });
	sprites["Characterbox3"]->SetScale({ 1.5f , 1.5f });
	sprites["Characterbox4"]->SetScale({ 1.5f , 1.5f });

	for (int i = 1; i <= 4; i++)
	{
		selectBoxs.push_back
			(sprites["Characterbox" + std::to_string(i)]);
	}
	
	//************************캐릭터 이미지************************
	NewSpriteGo("Character1Img", characterTable[0].textureId);
	NewSpriteGo("Character2Img", characterTable[1].textureId);
	NewSpriteGo("Character3Img", characterTable[2].textureId);
	NewSpriteGo("Character4Img", characterTable[3].textureId);

	//************************확인 이미지************************
	NewSpriteGo("ConfirmationIma", DT_STRING->Get("COMFIRM_IMG"));
	sprites["ConfirmationIma"]->sortLayer = 7;
	sprites["ConfirmationIma"]->SetOrigin(Origins::MC);
	sprites["ConfirmationIma"]->SetScale({ 1.5f , 2.f });
	sprites["ConfirmationIma"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f , FRAMEWORK.GetWindowSize().y * 0.5f, });

	//************************확인 박스************************
	NewSpriteGo("CheckBoxNo", DT_STRING->Get("CHECK_BOX"));
	sprites["CheckBoxNo"]->sortLayer = 8;
	sprites["CheckBoxNo"]->SetOrigin(Origins::MC);
	sprites["CheckBoxNo"]->SetScale({ 0.25f , 0.5f });
	sprites["CheckBoxNo"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f - 100.f, FRAMEWORK.GetWindowSize().y * 0.54f, });

	NewSpriteGo("CheckBoxYes", DT_STRING->Get("CHECK_BOX"));
	sprites["CheckBoxYes"]->sortLayer = 8;
	sprites["CheckBoxYes"]->SetOrigin(Origins::MC);
	sprites["CheckBoxYes"]->SetScale({ 0.25f , 0.5f });
	sprites["CheckBoxYes"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f + 100.f, FRAMEWORK.GetWindowSize().y * 0.54f, });

	checkBoxs.push_back(sprites["CheckBoxNo"]);
	checkBoxs.push_back(sprites["CheckBoxYes"]);

	//************************확인 텍스트************************
	NewTextGo("ConfirmationText", font, L"이 캐릭터를 선택하시겠습니까?", 30, sf::Color::White);
	texts["ConfirmationText"]->SetCharacterSize(60);
	texts["ConfirmationText"]->SetOrigin(Origins::MC);
	texts["ConfirmationText"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f , FRAMEWORK.GetWindowSize().y * 0.45f, });

	NewTextGo("NoText", font, L"아니요", 30, sf::Color::White);
	NewTextGo("YesText", font, L"예", 30, sf::Color::White);
	texts["NoText"]->SetOrigin(Origins::MC);
	texts["YesText"]->SetOrigin(Origins::MC);

	texts["NoText"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f - 100.f, FRAMEWORK.GetWindowSize().y * 0.535f, });
	texts["YesText"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f + 95.f, FRAMEWORK.GetWindowSize().y * 0.535f, });

	//***************************레이어****************************
	sprites["Character1Img"]->sortLayer = 12;
	sprites["Character2Img"]->sortLayer = 12;
	sprites["Character3Img"]->sortLayer = 12;
	sprites["Character4Img"]->sortLayer = 12;

	sprites["Characterbox1"]->sortLayer = 6;
	sprites["Characterbox2"]->sortLayer = 6;
	sprites["Characterbox3"]->sortLayer = 6;
	sprites["Characterbox4"]->sortLayer = 6;

	//***************************포지션****************************
	sprites["Character1Img"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.305f , FRAMEWORK.GetWindowSize().y * 0.23f });
	sprites["Character1Img"]->SetScale({ 3.f , 3.f });

	sprites["Character2Img"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.415f , FRAMEWORK.GetWindowSize().y * 0.24f });
	sprites["Character2Img"]->SetScale({ 3.5f , 3.5f });

	sprites["Character3Img"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.515f , FRAMEWORK.GetWindowSize().y * 0.24f });
	sprites["Character3Img"]->SetScale({ 1.f , 1.f });

	sprites["Character4Img"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.62f , FRAMEWORK.GetWindowSize().y * 0.24f });
	sprites["Character4Img"]->SetScale({ 0.6f , 0.6f });

	//*************************박스 포지션*************************
	sprites["Characterbox1"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.3f , FRAMEWORK.GetWindowSize().y * 0.2f });

	sprites["Characterbox2"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.4f , FRAMEWORK.GetWindowSize().y * 0.2f });

	sprites["Characterbox3"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.5f , FRAMEWORK.GetWindowSize().y * 0.2f });

	sprites["Characterbox4"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.6f , FRAMEWORK.GetWindowSize().y * 0.2f });

	//************************캐릭터 텍스트************************
	NewTextGo("Character1Name", font, characterTable[0].nameId, 30, sf::Color::White);
	texts["Character1Name"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.31f , FRAMEWORK.GetWindowSize().y * 0.21f });

	NewTextGo("Character2Name", font, characterTable[1].nameId, 30, sf::Color::White);
	texts["Character2Name"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.41f , FRAMEWORK.GetWindowSize().y * 0.21f });

	NewTextGo("Character3Name", font, characterTable[2].nameId, 30, sf::Color::White);
	texts["Character3Name"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.51f , FRAMEWORK.GetWindowSize().y * 0.21f });

	NewTextGo("Character4Name", font, characterTable[3].nameId, 30, sf::Color::White);
	texts["Character4Name"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.61f , FRAMEWORK.GetWindowSize().y * 0.21f });

	//*************************설명 텍스트*************************
	NewTextGo("CharacterDesc", font, L"", 40, sf::Color::White);
	texts["CharacterDesc"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.31f , FRAMEWORK.GetWindowSize().y * 0.8f });

	texts["CharacterDesc"]->sortLayer = 6;

	UiInit();


	ObjectsSort();
	
	// SetActive
	SetCheck(false);

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


	HandleMouseSelection();

	//std::cout << mouse->GetPosition().x << " " <<
	//	mouse->GetPosition().y << std::endl;
}

void UICharacterSelect::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}

void UICharacterSelect::SetCheck(bool c)
{
	sprites["ConfirmationIma"]->SetActive(c);
	sprites["CheckBoxNo"]->SetActive(c);
	sprites["CheckBoxYes"]->SetActive(c);
	texts["ConfirmationText"]->SetActive(c);
	texts["NoText"]->SetActive(c);
	texts["YesText"]->SetActive(c);
}

void UICharacterSelect::HandleMouseSelection()
{
	for (int i = 0; i < 4; i++)
	{
		if (selectBoxs[i]->GetGlobalBounds().contains(mouse->GetPosition()))
		{
			selectBoxs[i]->SetTexture("graphics/character_select_boxgreen.PNG");
			texts["CharacterDesc"]->SetString(characterTable[i].descId);
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				SOUND_MGR.PlaySfx("sound/ui/select.wav");
				SetCheck(true);
				playerIndex = i;
			}
			break;
		}
		else
		{
			selectBoxs[i]->SetTexture("graphics/character_select_box.PNG");
			texts["CharacterDesc"]->SetString(L"");
		}
	}

	for (int j = 0; j < checkBoxs.size(); j++)
	{
		if (checkBoxs[j]->GetGlobalBounds().contains(mouse->GetPosition()))
		{
			checkBoxs[j]->SetTexture(DT_STRING->Get("CHECK_BOX_GREEN"));

			// 아니요
			if (j == 0 && InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				SOUND_MGR.PlaySfx("sound/ui/select.wav");
				SetCheck(false);
				return;
			}
			// 예
			else if (j == 1 && InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				SOUND_MGR.PlaySfx("sound/ui/select.wav");
				SetCheck(false);
				Player* player = dynamic_cast<Player*>
					(SCENE_MGR.GetScene(SceneIds::SceneGame)->FindGo("Player"));
				player->SetPlayerType((Player::TYPES)playerIndex);
				SCENE_MGR.ChangeScene(SceneIds::SceneGame);
				SetActive(false);
				return;
			}
		}
		else
		{
			checkBoxs[j]->SetTexture(DT_STRING->Get("CHECK_BOX"));
		}
	}
}
