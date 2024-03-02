#include "pch.h"
#include "EffectCenterText.h"

EffectCenterText::EffectCenterText(Scene* sc, const std::string& name)
	:TextGo(sc, name)
{
	sortLayer = 17;
}

EffectCenterText::EffectCenterText(const std::string& name)
	:TextGo(name)
{
	sortLayer = 17;
}

void EffectCenterText::Init()
{
	TextGo::Init();
	color = { 255, 255, 255, 255 };
	colorOut = { 0,0,0,255 };
	SetFont("fonts/DOSIyagiBoldface.ttf");
	SetColor(color);
	SetCharacterSize(70);
	SetOutLine(5.f, colorOut);
	SetPosition(sf::Vector2f(FRAMEWORK.GetWindowSize()) * 0.5f);
}

void EffectCenterText::Update(float dt)
{
	TextGo::Update(dt);
	timer += dt;
	if (timer >= duration)
	{
		timer2 -= dt;
		if (timer2 > 0.f)
		{
			colorOut.a = color.a = (int)(timer2/duration2 * 255);
		}
		else if(active)
		{
			colorOut.a = color.a = 0;
			active = false;
			scene->DeleteGo(this);
		}
	}
	SetColor(color);
	SetOutLine(5.f, colorOut);
}

void EffectCenterText::Draw(sf::RenderWindow& window)
{
	TextGo::Draw(window);
}

EffectCenterText* EffectCenterText::Create(Scene* sc, const std::wstring& text)
{
	EffectCenterText* ef = new EffectCenterText(sc);
	ef->Init();
	ef->SetString(text);
	ef->SetOrigin(Origins::BC);
	sc->AddGo(ef,Scene::Ui);
	return ef;
}
