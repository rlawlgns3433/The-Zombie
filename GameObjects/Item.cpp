#include "pch.h"
#include "Item.h"
#include "Player.h"
#include "Scene.h"
#include "ItemTable.h"


Item::Item(const std::string& name)
	:SpriteGo(name), type(Types::NONE), value(0), player(nullptr)
{
	sortLayer = 2;
}

Item::Item(Scene* sc, const std::string& name)
	:SpriteGo(sc,name), type(Types::NONE), value(0), player(nullptr)
{
	sortLayer = 2;
}

void Item::Init()
{
	SpriteGo::Init();
}

void Item::Release()
{
	SpriteGo::Release();
}

void Item::Reset()
{
	SpriteGo::Reset();
	SetOrigin(Origins::MC);
	player = dynamic_cast<Player*>(scene->FindGo("Player"));
}

void Item::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Item::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);
}

void Item::FixedUpdate(float dt)
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

void Item::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

Item* Item::Create(Types t, Scene* sc, int v)
{
	Item* newItem = new Item(sc);
	newItem->type = t;

	const DATA_ITEM& data = DT_ITEM->Get(newItem->type);

	if (v == 0)
	{
	newItem->value = Utils::RandomRange(data.minVal, data.maxVal);
	}
	else
	{
		newItem->value = v;
	}


	newItem->textureId = data.textureId;
	newItem->Init();
	newItem->Reset();
	newItem->scene->AddGo(newItem);
	return newItem;
}
