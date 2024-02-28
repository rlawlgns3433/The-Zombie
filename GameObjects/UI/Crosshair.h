#pragma once
#include "SpriteGo.h"
class Crosshair : public SpriteGo
{
public:
	Crosshair(const std::string& name = "crosshair");
	~Crosshair() override = default;

	void Init();
	void Release();
	void Reset();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	bool isPlaying = false;

	sf::Vector2f defaultScale;
	float defaultRotation;
	float motionSpeed = 2.f;

	void MotionUpdate(float dt);
	void MotionReload(float reloadSpeed);
	void MotionShot();

	sf::Vector2f GetPosition() const { return position; }
};

