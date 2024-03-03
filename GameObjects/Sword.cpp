#include "pch.h"
#include "Sword.h"
#include "UIHUD.h"
#include "SwordAttack.h"
#include "Bullet.h"
#include "SceneGame.h"

Sword::Sword(Player* player, const std::string& name)
	: Weapon(name)
{
	this->player = player;
	scene = this->player->GetScene();
}

void Sword::Init()
{
	Weapon::Init();
}

void Sword::Release()
{
	Weapon::Release();
}

void Sword::Reset()
{
	Weapon::Reset();
	type = Types::Cloased;
	hud = dynamic_cast<UIHUD*>((SCENE_MGR.GetScene(SceneIds::SceneGame))->FindGo("UIHUD"));
	hud->SetAmmo(ammo, totalAmmo);
	ammo = maxAmmo;
	totalAmmo = ammo;

	damage = 34;
	shotInterval = 0.05f;
}

void Sword::Update(float dt)
{
	Weapon::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		Reload();
	}
}

void Sword::LateUpdate(float dt)
{
	Weapon::LateUpdate(dt);
}

void Sword::FixedUpdate(float dt)
{
	Weapon::FixedUpdate(dt);
}

void Sword::Draw(sf::RenderWindow& window)
{
	Weapon::Draw(window);
}

void Sword::Attack()
{
	if (!player->GetActive()) return;

	if (ammo > 0)
	{
		ammo--;
		hud->SetAmmo(ammo, totalAmmo);

		SwordAttack* swordAttack = SwordAttack::Create(scene, player);
		swordAttack->Init();
		swordAttack->Reset();
		swordAttack->SetDamage(player->GetWeapon()->GetDamage());

		scene->AddGo(swordAttack);
		dynamic_cast<SceneGame*>(scene)->bullets.push_back(swordAttack);

		SOUND_MGR.PlaySfx("sound/sword/sword"+ std::to_string(Utils::RandomRange(0, 3)) +".wav");
	}
	else
	{
		Reload();
	}
}

void Sword::Reload()
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
