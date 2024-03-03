#pragma once
#include "TextGo.h"
class EffectCenterText : public TextGo
{
protected:
	EffectCenterText(Scene* sc, const std::string& name = "CenterText");
	EffectCenterText(const std::string& name = "CenterText");

	sf::Color color;
	sf::Color colorOut;

	float timer = 0.f;

public:
	~EffectCenterText() override = default;

	EffectCenterText(const EffectCenterText&) = delete;
	EffectCenterText(EffectCenterText&&) = delete;
	EffectCenterText& operator=(const EffectCenterText&) = delete;
	EffectCenterText& operator=(EffectCenterText&&) = delete;

	float duration = 1.f;
	float duration2 = 2.f;

	void Init() override;
	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	static EffectCenterText* Create(Scene* sc, const std::wstring& text);
protected:
	float timer2 = duration2;
};

