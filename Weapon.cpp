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
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	player = dynamic_cast<Player*>(dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->FindGo("player"));
}

void Weapon::Update(float dt)
{
	GameObject::Update(dt);
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
