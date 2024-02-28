#include "pch.h"
#include "EffectDamage.h"

EffectDamage::EffectDamage(Scene* scene, const std::string& name)
    :TextGo(scene, name)
{
    sortLayer = 11;
}

EffectDamage::EffectDamage(const std::string& name)
    :TextGo(name)
{
    sortLayer = 11;
}

void EffectDamage::Init()
{
    TextGo::Init();
    SetFont("fonts/BMHANNAPro.ttf");
    SetCharacterSize(15);
    SetColor(sf::Color(255,255,255,180));
    SetOutLine(1.f, sf::Color(50,50,50,180));
    SetString(L"¹ÌÀÔ·Â");
    SetOrigin(Origins::MC);
}

void EffectDamage::Update(float dt)
{
    TextGo::Update(dt);
    timer += dt;
    if (timer >= duration)
    {
        scene->DeleteGo(this);
    }
}

void EffectDamage::Draw(sf::RenderWindow& window)
{
    TextGo::Draw(window);
}

EffectDamage* EffectDamage::Create(Scene* sc, sf::Vector2f pos, const std::wstring& text)
{
    EffectDamage* ef = new EffectDamage(sc);
    ef->Init();
    ef->SetString(text);
    ef->SetOrigin(Origins::MC);
    ef->SetPosition(pos);
    sc->AddGo(ef);
    return nullptr;
}

EffectDamage* EffectDamage::Create(Scene* sc, sf::Vector2f pos, int damage)
{
    Create(sc, pos, std::to_wstring(damage));
    return nullptr;
}
