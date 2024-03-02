#include "pch.h"
#include "Wand.h"
#include "Player.h"
#include "EffectCenterText.h"
#include "EffectLightLine.h"
#include "Crosshair.h"
#include "Flame.h"
#include <Bullet.h>


Wand::Wand(Player* player, const std::string& name)
	:Weapon(name)
{
	this->player = player;
	scene = player->GetScene();
	playerSpeed = player->GetSpeed();
	damage = 100.f;
	Combo();
}

void Wand::Release()
{
	Weapon::Release();
	for (auto ptr : comboList)
	{
		if (ptr != nullptr)
		{
			delete ptr;
		}
	}
	comboList.clear();
}

void Wand::Update(float dt)
{
	GameObject::Update(dt);
	//기존의 Attack을 대신하여 우클릭은 시전 취소
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		Attack();
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Right))
	{
		MagicCancle();
	}

	//콤보 검사 및 마법 시전
	if (isChanneling)
	{
		comboTimer += dt;
		EffectLightLine::Create(scene, player, player->GetPosition() + Utils::RandomOnUnitCircle() * 200.f);

		if (comboTimer >= comboTimeLimit)
		{
			MagicCancle();
			if (InputMgr::IsComboSuccess(*comboList[comboSelected]))
			{
				MagicAttack();
			}
		}
		else if (InputMgr::IsComboSuccess(*comboList[comboSelected]))
		{
			MagicCancle();
			MagicAttack();
		}
	}
}

void Wand::Attack()
{
	MagicChanneling();
}

void Wand::MagicChanneling()
{
	if (!isChanneling)
	{
		SOUND_MGR.PlaySfx("sound/magic/channeling.wav");
		FRAMEWORK.GetMouse()->MotionReload(comboTimeLimit);

		isChanneling = true;
		playerSpeed = playerSpeed = player->GetSpeed();
		player->SetSpeed(0.f);

		std::wstring comboWord;
		comboSelected = Utils::RandomRange(0, comboList.size());
		for (auto& i : *(comboList[comboSelected]))
		{
			comboWord += static_cast<char>(i.first + 65);
		}
		EffectCenterText::Create(scene, comboWord);

		InputMgr::StopComboRecord();
		InputMgr::ClearCombo();
		InputMgr::ComboRecord(comboTimeLimit);
	}
}

void Wand::MagicAttack()
{
	FRAMEWORK.GetMouse()->MotionReload(0.f);
	switch (comboSelected)
	{
	case 0:
		Flame::Create(scene, player);
		SOUND_MGR.PlaySfx("sound/fire.wav");
		break;
	case 1:
		Bullet::Create(scene);
		SOUND_MGR.PlaySfx("sound/shoot.wav");
		break;
	default:
		break;
	}


}

void Wand::MagicCancle()
{
	if (isChanneling)
	{
		isChanneling = false;
		comboTimer = 0.f;
		player->SetSpeed(playerSpeed);
		InputMgr::StopComboRecord();
		FRAMEWORK.GetMouse()->MotionShot();
		FRAMEWORK.GetMouse()->MotionReload(0.f);
		SOUND_MGR.PlaySfx("sound/magic/cancle.wav");
	}
}

void Wand::Combo()
{
	InputMgr::SFGM_COMBO* fire = new InputMgr::SFGM_COMBO;
	comboList.push_back(fire);
	fire->push_back(std::make_pair(sf::Keyboard::F, InputMgr::KEY_STATE::DOWN));
	fire->push_back(std::make_pair(sf::Keyboard::I, InputMgr::KEY_STATE::DOWN));
	fire->push_back(std::make_pair(sf::Keyboard::R, InputMgr::KEY_STATE::DOWN));
	fire->push_back(std::make_pair(sf::Keyboard::E, InputMgr::KEY_STATE::DOWN));

	InputMgr::SFGM_COMBO* gun = new InputMgr::SFGM_COMBO;
	comboList.push_back(gun);
	gun->push_back(std::make_pair(sf::Keyboard::G, InputMgr::KEY_STATE::DOWN));
	gun->push_back(std::make_pair(sf::Keyboard::U, InputMgr::KEY_STATE::DOWN));
	gun->push_back(std::make_pair(sf::Keyboard::N, InputMgr::KEY_STATE::DOWN));
}