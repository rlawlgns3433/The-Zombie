#include "pch.h"
#include "Crosshair.h"

Crosshair::Crosshair(const std::string& name)
	:SpriteGo(name), defaultScale(0.7f, 0.7f), defaultRotation(0.f)
{
	sortLayer = 20;
	textureId = "graphics/crosshair.png";
	SetTexture(textureId);
	SetOrigin(Origins::MC);
}

void Crosshair::Init()
{
	SpriteGo::Init();
}

void Crosshair::Release()
{
	SpriteGo::Release();
}

void Crosshair::Reset()
{
	SpriteGo::Reset();
}

void Crosshair::Update(float dt)
{
	SpriteGo::Update(dt);
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToUi((sf::Vector2i)InputMgr::GetMousePos());
	SetPosition(mouseWorldPos);
	MotionUpdate(dt);
}

void Crosshair::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Crosshair::MotionUpdate(float dt)
{
	bool doUpdate = false;
	if (scale.x > defaultScale.x)
	{
		scale.x = std::max(defaultScale.x, scale.x - motionSpeed * dt);
		doUpdate = true;
	}
	if (scale.y > defaultScale.y)
	{
		scale.y = std::max(defaultScale.y, scale.y - motionSpeed * dt);
		doUpdate = true;
	}
	if (rotation != defaultRotation)
	{
		rotation = std::max(0.f,rotation - 90.f*dt);
		doUpdate = true;
	}

	if (!isPlaying&&InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
	{
		MotionShot();
	}


	if (doUpdate)
	{
		SetScale(scale);
		SetRotation(rotation);
	}
}

void Crosshair::MotionReload(float reloadSpeed)
{
	SetRotation(90.f*reloadSpeed);
}

void Crosshair::MotionShot()
{
	SetScale({ 1.0f, 1.0f });
}
