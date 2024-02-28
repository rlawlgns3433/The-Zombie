#include "pch.h"
#include "Weapon.h"
#include "Player.h"
#include "SceneGame.h"
#include "UIHUD.h"

Weapon::Weapon(const std::string& name)
	: GameObject(name)
{
}

void Weapon::Init()
{
	GameObject::Init();
	hud = dynamic_cast<UIHUD*>((SCENE_MGR.GetScene(SceneIds::SceneGame))->FindGo("UIHUD"));
	hud->SetAmmo(ammo, totalAmmo);
}

void Weapon::Release()
{
	GameObject::Release();
}

void Weapon::Reset()
{
	GameObject::Reset();
	hud->SetAmmo(ammo, totalAmmo);
}

void Weapon::Update(float dt)
{
	GameObject::Update(dt);

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
}

void Weapon::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}

void Weapon::FixedUpdate(float dt)
{
	GameObject::FixedUpdate(dt);
}

void Weapon::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
}


void  Weapon::AddMaxAmmo(int value)
{
	maxAmmo = std::max(1, maxAmmo + value);
	hud->SetAmmo(ammo, totalAmmo);
}
void  Weapon::AddShotInterval(float value)
{
	shotInterval = std::max(0.01f, shotInterval + value);
}
void  Weapon::AddDamage(int value)
{
	damage = std::max(1, damage + value);
}
void  Weapon::AddReloadSpeed(float value)
{
	reloadSpeed = std::max(0.f, reloadSpeed + value);
}

void Weapon::AddTotalAmmo(int add)
{
	totalAmmo += add;
	hud->SetAmmo(ammo, totalAmmo);
}
