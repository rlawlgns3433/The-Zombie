#pragma once
#include "TextGo.h"
class EffectDamage : public TextGo
{
private:
	EffectDamage(Scene* scene, const std::string& name = "Damage");
	EffectDamage(const std::string& name = "Damage");

	float timer = 0.0f;
	float duration = 0.5f;

	void Init() override;
	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

public:
	~EffectDamage() override = default;
	static EffectDamage* Create(Scene* sc, sf::Vector2f pos, const std::wstring& text);
	static EffectDamage* Create(Scene* sc, sf::Vector2f pos, int damage);
};

