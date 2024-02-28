#include "pch.h"
#include "Item2.h"
#include "Player.h"
#include "Scene.h"

Item2::Item2(const std::string& name)
	:SpriteGo(name), type(Types::NONE), value(0), player(nullptr)
{
}

Item2::Item2(Scene* sc, const std::string& name)
	:SpriteGo(sc,name), type(Types::NONE), value(0), player(nullptr)
{
}

void Item2::Init()
{
	SpriteGo::Init();
}

void Item2::Release()
{
	SpriteGo::Release();
}

void Item2::Reset()
{
	SpriteGo::Reset();
	SetOrigin(Origins::MC);
	player = dynamic_cast<Player*>(scene->FindGo("Player"));
}

void Item2::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Item2::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);
}

void Item2::FixedUpdate(float dt)
{
	SpriteGo::FixedUpdate(dt);

	if (player == nullptr)
		return;
	if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
	{
		SetActive(false);
		SCENE_MGR.GetCurrentScene()->DeleteGo(this);
		player->onItem(this);
	}
}

void Item2::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

Item2* Item2::Create(Types t, int v, Scene* sc)
{
	Item2* newItem = new Item2(sc);
	newItem->type = t;
	newItem->value = v;

	switch (newItem->type)
	{
	case Types::AMMO:
		newItem->textureId = "graphics/ammo_pickup.png";
		break;
	case Types::HEALTH:
		newItem->textureId = "graphics/health_pickup.png";
		break;
	}


	newItem->Init();
	newItem->Reset();
	newItem->scene->AddGo(newItem);
	return newItem;
}
