#include "pch.h"
#include "FlameThrower.h"
#include "UIHUD.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Flame.h"

FlameThrower::FlameThrower(Player* player, const std::string& name)
	: Weapon(name)
{
	this->player = player;
	scene = this->player->GetScene();
}

void FlameThrower::Init()
{
	Weapon::Init();
}

void FlameThrower::Release()
{
	Weapon::Release();
}

void FlameThrower::Reset()
{
	Weapon::Reset();
	type = Types::Cloased;

	hud = dynamic_cast<UIHUD*>((SCENE_MGR.GetScene(SceneIds::SceneGame))->FindGo("UIHUD"));
	hud->SetAmmo(ammo, totalAmmo);
	ammo = maxAmmo;
	totalAmmo = ammo;

	damage = 34;
	attackInterval = 0.05f;
}

void FlameThrower::Update(float dt)
{
	Weapon::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		Reload();
	}
}

void FlameThrower::LateUpdate(float dt)
{
	Weapon::LateUpdate(dt);
}

void FlameThrower::FixedUpdate(float dt)
{
	Weapon::FixedUpdate(dt);
}

void FlameThrower::Draw(sf::RenderWindow& window)
{
	Weapon::Draw(window);
}

void FlameThrower::Attack()
{
	if (!player->GetActive()) return;

	if (ammo > 0)
	{
		ammo--;
		hud->SetAmmo(ammo, totalAmmo);

		Flame* flame = new Flame(player);
		flame->Init();
		flame->Reset();
		scene->AddGo(flame);
		dynamic_cast<SceneGame*>(scene)->bullets.push_back(flame);

		SOUND_MGR.PlaySfx("sound/shoot.wav");
	}
	else
	{
		Reload();
	}
}

void FlameThrower::Reload()
{
	shotTimer = -0.05f;
	int needAmmo = maxAmmo - ammo;
	if (totalAmmo >= needAmmo)
	{
		ammo += needAmmo;
		totalAmmo -= needAmmo;
		hud->SetAmmo(ammo, totalAmmo);
		SOUND_MGR.PlaySfx("sound/reload.wav");
	}
	else if (totalAmmo == 0)
	{
		SOUND_MGR.PlaySfx("sound/reload_failed.wav");
	}
	else
	{
		ammo += totalAmmo;
		totalAmmo = 0;
		hud->SetAmmo(ammo, totalAmmo);
		SOUND_MGR.PlaySfx("sound/reload.wav");
	}
}
