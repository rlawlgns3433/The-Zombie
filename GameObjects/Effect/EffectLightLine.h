#pragma once
#include "GameObject.h"
class EffectLightLine : public GameObject
{
	EffectLightLine(Scene* sc, const std::string& name = "");
	sf::Vector2f direction;
public:
	sf::VertexArray light;
	GameObject* object;

	~EffectLightLine() override = default;

	EffectLightLine(const EffectLightLine&) = delete;
	EffectLightLine(EffectLightLine&&) = delete;
	EffectLightLine& operator=(const EffectLightLine&) = delete;
	EffectLightLine& operator=(EffectLightLine&&) = delete;

	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	static void Create(Scene* sc, GameObject* obj, sf::Vector2f pos1);
};
