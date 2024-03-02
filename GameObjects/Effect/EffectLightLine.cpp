#include "pch.h"
#include "EffectLightLine.h"

EffectLightLine::EffectLightLine(Scene* sc, const std::string& name)
	:GameObject(sc, name), object(nullptr)
{
	light = sf::VertexArray(sf::Lines, 2);
	light[0].color = sf::Color::Yellow;
	light[1].color = sf::Color::White;
}

void EffectLightLine::FixedUpdate(float dt)
{
	Utils::Normalize(direction = object->GetPosition() - light[0].position);
	light[0].position += direction * 2000.f* dt;
	Utils::Normalize(direction = object->GetPosition() - light[1].position);
	light[1].position += direction * 1000.f* dt;
	if (Utils::Distance(object->GetPosition(), light[1].position) <= 10.f)
	{
		scene->DeleteGo(this);
	}
}

void EffectLightLine::Draw(sf::RenderWindow& window)
{
	window.draw(light);
}

void EffectLightLine::Create(Scene* sc, GameObject* obj, sf::Vector2f pos1)
{
	EffectLightLine* eLL = new EffectLightLine(sc);
	eLL->object = obj;
	eLL->light[0].position = pos1;
	eLL->light[1].position = pos1;
	eLL->scene->AddGo(eLL);
}
