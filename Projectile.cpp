#include "pch.h"
#include "Projectile.h"

Projectile::Projectile(const std::string& name)
	: GameObject(name)
{
	sortLayer = 4;
	tag = 1;
}

void Projectile::Init()
{
}

void Projectile::Release()
{
}

void Projectile::Reset()
{
}

void Projectile::Update(float dt)
{
}

void Projectile::LateUpdate(float dt)
{
}

void Projectile::FixedUpdate(float dt)
{
}

void Projectile::Draw(sf::RenderWindow& window)
{
}

void Projectile::Hit()
{
	if (!isHit)
	{
		isHit = true;
	}
}