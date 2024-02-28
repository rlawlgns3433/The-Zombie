#pragma once
#include "SpriteGo.h"
class Player;

class Item: public SpriteGo
{
public:
	enum class Types
	{
		NONE = -1,
		AMMO,
		HEALTH,


		COUNT,
	};
protected:
	Types type;
	int value;

	Player* player;

public:
	Item(const std::string& name = "");
	Item(Scene* sc, const std::string& name = "");
	~Item() override = default;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	static Item* Create(Types t, int v, Scene* sc);
	Types GetType() const { return type; }
	int GetValue()const { return value; }

};