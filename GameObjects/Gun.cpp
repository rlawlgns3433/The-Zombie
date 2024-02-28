#include "pch.h"
#include "Gun.h"
#include "UIHUD.h"
#include "Bullet.h"
#include "SceneGame.h"

Gun::Gun(Player* player, const std::string& name)
	: Weapon(name)
{
	this->player = player;
	scene = this->player->GetScene();
}

void Gun::Init()
{
	Weapon::Init();
}

void Gun::Release()
{
	Weapon::Release();
	type = Types::Cloased;
}

void Gun::Reset()
{
	Weapon::Reset();


	ammo = maxAmmo;
	totalAmmo = ammo;

	damage = 34;
	shotInterval = 0.2f;
	reloadSpeed = 1.f;
}

void Gun::Update(float dt)
{
	Weapon::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		Reload();
	}
}

void Gun::LateUpdate(float dt)
{
	Weapon::LateUpdate(dt);
}

void Gun::FixedUpdate(float dt)
{
	Weapon::FixedUpdate(dt);
}

void Gun::Draw(sf::RenderWindow& window)
{
	Weapon::Draw(window);
}

void Gun::Attack()
{
	if (!player->GetActive()) return;

	if (ammo > 0)
	{
		ammo--;
		hud->SetAmmo(ammo, totalAmmo);

		Bullet::Create(scene);


		SOUND_MGR.PlaySfx("sound/shoot.wav");
	}
	else
	{
		Reload();
	}
}

void Gun::Reload()
{
	shotTimer = -reloadSpeed;
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
