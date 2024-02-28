#include "pch.h"
#include "FlameThrower.h"
#include "UIHUD.h"
#include "Bullet.h"
#include "SceneGame.h"

FlameThrower::FlameThrower(const std::string& name)
	: Weapon(name)
{
}

void FlameThrower::Init()
{
	Weapon::Init();
}

void FlameThrower::Release()
{
}

void FlameThrower::Reset()
{
	Weapon::Reset();
	type = Types::Ranged;

}

void FlameThrower::Update(float dt)
{
	Weapon::Update(dt);
}

void FlameThrower::LateUpdate(float dt)
{
}

void FlameThrower::FixedUpdate(float dt)
{
}

void FlameThrower::Draw(sf::RenderWindow& window)
{
}

void FlameThrower::Attack()
{
	
}

void FlameThrower::Reload()
{
}
