#include "pch.h"
#include "Wand.h"
#include "Player.h"
#include "EffectCenterText.h"
#include "EffectLightLine.h"
#include "Crosshair.h"
#include "Flame.h"
#include "Bullet.h"
#include "Lighting.h"
#include "UIHUD.h"


Wand::Wand(Player* player, const std::string& name)
	:Weapon(name)
{
	this->player = player;
	scene = player->GetScene();
	playerSpeed = player->GetSpeed();
	damage = 100.f;
	maxAmmo = 5;
	ammo = maxAmmo;
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

	if (perfectTimer > 0.f)
	{
		perfectTimer -= dt;
	}

	if (shotTimer < shotInterval)
	{
		shotTimer += dt;
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		if (shotTimer >= 0.f)
		{
			Attack();
		}
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Right))
	{
		MagicCancle();
	}

	//기존의 Attack을 대신하여 우클릭은 시전 취소

	if (!isChanneling && InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		Reload();
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
		else if (InputMgr::IsPerfectCombo(*comboList[comboSelected]))
		{
			MagicCancle();
			MagicPerfect();
		}
		else if (InputMgr::IsExllentCombo(*comboList[comboSelected]))
		{
			MagicCancle();
			MagicExcellent();
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
	if (ammo <= 0)
	{
		Reload();
		return;
	}



	if (perfectTimer > 0.f)
	{
		ammo--;
		hud->SetAmmo(ammo, totalAmmo);
		Lighting::Create(scene);
		SOUND_MGR.PlaySfx("sound/magic/lightning.wav");
	}
	else
	{
		MagicChanneling();
	}
}

void Wand::MagicChanneling()
{
	if (!isChanneling)
	{
		ammo--;
		hud->SetAmmo(ammo, totalAmmo);

		SOUND_MGR.PlaySfx("sound/magic/channeling.wav");
		FRAMEWORK.GetMouse()->MotionReload(comboTimeLimit);

		isChanneling = true;
		playerSpeed = playerSpeed = player->GetSpeed();
		player->SetSpeed(0.f);

		std::wstring comboWord;
		comboSelected = Utils::RandomRange(0, comboList.size());
		for (auto& i : *(comboList[comboSelected]))
		{
			if (i.second == InputMgr::KEY_STATE::UP)
			{
				continue;
			}
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
	case 2:
		Lighting::Create(scene);
		SOUND_MGR.PlaySfx("sound/magic/lightning.wav");
		break;
	default:
		break;
	}


}

void Wand::MagicExcellent()
{
	FRAMEWORK.GetMouse()->MotionReload(0.f);
	switch (comboSelected)
	{
	case 0:
		player->AddHp(1);
		Flame::Create(scene, player);
		SOUND_MGR.PlaySfx("sound/fire.wav");
		break;
	case 1:
		player->AddHp(1);
		Bullet::Create(scene);
		SOUND_MGR.PlaySfx("sound/shoot.wav");
		break;
	case 2:
		player->AddHp(1);
		Lighting::Create(scene);
		SOUND_MGR.PlaySfx("sound/magic/lightning.wav");
		break;
	default:
		break;
	}
}

void Wand::MagicPerfect()
{
	SOUND_MGR.PlaySfx("sound/magic/perfect.wav");
	FRAMEWORK.GetMouse()->MotionReload(0.f);

	switch (comboSelected)
	{
	case 0:
	case 1:
		Flame::Create(scene, player);
		Bullet::Create(scene);
		Lighting::Create(scene);
		SOUND_MGR.PlaySfx("sound/fire.wav");
		SOUND_MGR.PlaySfx("sound/shoot.wav");
		SOUND_MGR.PlaySfx("sound/magic/lightning.wav");
		break;
	case 2:
		Lighting::Create(scene);
		SOUND_MGR.PlaySfx("sound/magic/lightning.wav");
		perfectTimer = reloadSpeed;
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
	fire->push_back(std::make_pair(sf::Keyboard::F, InputMgr::KEY_STATE::UP));
	fire->push_back(std::make_pair(sf::Keyboard::I, InputMgr::KEY_STATE::DOWN));
	fire->push_back(std::make_pair(sf::Keyboard::I, InputMgr::KEY_STATE::UP));
	fire->push_back(std::make_pair(sf::Keyboard::R, InputMgr::KEY_STATE::DOWN));
	fire->push_back(std::make_pair(sf::Keyboard::R, InputMgr::KEY_STATE::UP));
	fire->push_back(std::make_pair(sf::Keyboard::E, InputMgr::KEY_STATE::DOWN));
	fire->push_back(std::make_pair(sf::Keyboard::E, InputMgr::KEY_STATE::UP));

	InputMgr::SFGM_COMBO* gun = new InputMgr::SFGM_COMBO;
	comboList.push_back(gun);
	gun->push_back(std::make_pair(sf::Keyboard::G, InputMgr::KEY_STATE::DOWN));
	gun->push_back(std::make_pair(sf::Keyboard::G, InputMgr::KEY_STATE::UP));
	gun->push_back(std::make_pair(sf::Keyboard::U, InputMgr::KEY_STATE::DOWN));
	gun->push_back(std::make_pair(sf::Keyboard::U, InputMgr::KEY_STATE::UP));
	gun->push_back(std::make_pair(sf::Keyboard::N, InputMgr::KEY_STATE::DOWN));
	gun->push_back(std::make_pair(sf::Keyboard::N, InputMgr::KEY_STATE::UP));

	InputMgr::SFGM_COMBO* lightning = new InputMgr::SFGM_COMBO;
	comboList.push_back(lightning);
	lightning->push_back(std::make_pair(sf::Keyboard::L, InputMgr::KEY_STATE::DOWN));
	lightning->push_back(std::make_pair(sf::Keyboard::L, InputMgr::KEY_STATE::UP));
	lightning->push_back(std::make_pair(sf::Keyboard::I, InputMgr::KEY_STATE::DOWN));
	lightning->push_back(std::make_pair(sf::Keyboard::I, InputMgr::KEY_STATE::UP));
	lightning->push_back(std::make_pair(sf::Keyboard::G, InputMgr::KEY_STATE::DOWN));
	lightning->push_back(std::make_pair(sf::Keyboard::G, InputMgr::KEY_STATE::UP));
	lightning->push_back(std::make_pair(sf::Keyboard::H, InputMgr::KEY_STATE::DOWN));
	lightning->push_back(std::make_pair(sf::Keyboard::H, InputMgr::KEY_STATE::UP));
	lightning->push_back(std::make_pair(sf::Keyboard::T, InputMgr::KEY_STATE::DOWN));
	lightning->push_back(std::make_pair(sf::Keyboard::T, InputMgr::KEY_STATE::UP));
	lightning->push_back(std::make_pair(sf::Keyboard::N, InputMgr::KEY_STATE::DOWN));
	lightning->push_back(std::make_pair(sf::Keyboard::N, InputMgr::KEY_STATE::UP));
	lightning->push_back(std::make_pair(sf::Keyboard::I, InputMgr::KEY_STATE::DOWN));
	lightning->push_back(std::make_pair(sf::Keyboard::I, InputMgr::KEY_STATE::UP));
	lightning->push_back(std::make_pair(sf::Keyboard::N, InputMgr::KEY_STATE::DOWN));
	lightning->push_back(std::make_pair(sf::Keyboard::N, InputMgr::KEY_STATE::UP));
	lightning->push_back(std::make_pair(sf::Keyboard::G, InputMgr::KEY_STATE::DOWN));
	lightning->push_back(std::make_pair(sf::Keyboard::G, InputMgr::KEY_STATE::UP));
}

void Wand::Reload()
{
	shotTimer = -reloadSpeed;
	FRAMEWORK.GetMouse()->MotionReload(reloadSpeed);

	int needAmmo = maxAmmo - ammo;
	if (totalAmmo >= needAmmo)
	{
		ammo += needAmmo;
		totalAmmo -= needAmmo;
		hud->SetAmmo(ammo, totalAmmo);
		SOUND_MGR.PlaySfx("sound/magic/reload.wav");
	}
	else if (totalAmmo == 0)
	{
		SOUND_MGR.PlaySfx("sound/magic/poka.wav");
	}
	else
	{
		ammo += totalAmmo;
		totalAmmo = 0;
		hud->SetAmmo(ammo, totalAmmo);
		SOUND_MGR.PlaySfx("sound/magic/reload.wav");
	}
}
