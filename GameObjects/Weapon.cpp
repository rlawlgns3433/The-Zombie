#include "pch.h"
#include "Weapon.h"
#include "Player.h"
#include "SceneGame.h"

Weapon::Weapon(const std::string& name)
	: GameObject(name)
{
}

void Weapon::Init()
{
	GameObject::Init();
}

void Weapon::Release()
{
	GameObject::Release();
}

void Weapon::Reset()
{
	GameObject::Reset();
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
