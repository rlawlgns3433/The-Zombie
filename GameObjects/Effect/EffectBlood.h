#pragma once
#include "SpriteGo.h"
class EffectBlood :
    public SpriteGo
{
protected:
	float timer = 5.f;
	bool del = false;
public:
	EffectBlood(sf::Vector2f pos, const std::string& name = "Blood");
	~EffectBlood()override = default;

	EffectBlood(const EffectBlood&) = delete;
	EffectBlood(EffectBlood&&) = delete;
	EffectBlood& operator=(const EffectBlood&) = delete;
	EffectBlood& operator=(EffectBlood&&) = delete;


	void Init() override;
	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;
};

