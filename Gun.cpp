#include "pch.h"
#include "Gun.h"
#include "UIHUD.h"
#include "Bullet.h"
#include "SceneGame.h"

Gun::Gun(const std::string& name)
	: Weapon(name)
{
}

void Gun::Init()
{
	Weapon::Init();
}

void Gun::Release()
{
	Weapon::Release();
}

void Gun::Reset()
{
	Weapon::Reset();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

	
	//dynamic_cast<UIHUD*>((SCENE_MGR.GetScene(SceneIds::SceneGame))->FindGo("UIHUD"))->SetAmmo(ammo, totalAmmo);

	ammo = maxAmmo;
	totalAmmo = ammo;

	damage = 34;
	attackInterval = 0.05f;
}

void Gun::Update(float dt)
{
	Weapon::Update(dt);
	shotTimer += dt;

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		if (shotTimer >= shotInterval)
		{
			shotTimer = 0.f;
			Attack();
		}
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Right))
	{
		if (shotTimer >= shotInterval)
		{
			shotTimer = 0.f;
			Attack();
		}
	}

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
	if (ammo > 0)
	{
		ammo--;
		//hud->SetAmmo(ammo, totalAmmo);

		Bullet* b = Bullet::Create(player);
		b->Init();
		b->Reset();
		SCENE_MGR.GetCurrentScene()->AddGo(b);
		dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->bullets.push_back(b);

		//dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->crosshair->MotionShot();
		SOUND_MGR.PlaySfx("sound/shoot.wav");
	}
	else
	{
		Reload();
	}
}

void Gun::Reload()
{
	shotTimer = -0.5f;
	int needAmmo = maxAmmo - ammo;
	if (totalAmmo >= needAmmo)
	{
		ammo += needAmmo;
		totalAmmo -= needAmmo;
		//hud->SetAmmo(ammo, totalAmmo);
		SOUND_MGR.PlaySfx("sound/reload.wav");
		//dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->crosshair->MotionReload();
	}
	else if (totalAmmo == 0)
	{
		SOUND_MGR.PlaySfx("sound/reload_failed.wav");
	}
	else
	{
		ammo += totalAmmo;
		totalAmmo = 0;
		//hud->SetAmmo(ammo, totalAmmo);
		SOUND_MGR.PlaySfx("sound/reload.wav");
		//dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->crosshair->MotionReload();
	}
}
