#include "pch.h"
#include "UIHUD.h"

UIHUD::UIHUD(const std::string& name)
	:GameObject(name)
{
}

void UIHUD::Init()
{
	GameObject::Init();

	//Init
	textScore.Init();
	textHiScore.Init();
	imgAmmoIcon.Init();
	textAmmo.Init();
	textWave.Init();
	textZombieCount.Init();

	//SetContent
	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");
	sf::Font& font2 = RES_MGR_FONT.Get("fonts/BMHANNAPro.ttf");
	imgAmmoIcon.SetTexture("graphics/ammo_icon.png");

	textScore.Set(font, "", textSize, sf::Color::White);
	textHiScore.Set(font, "", textSize, sf::Color::White);
	textAmmo.Set(font, "", textSize, sf::Color::Yellow);
	textWave.Set(font, "", textSize, sf::Color::White);
	textZombieCount.Set(font, "", textSize, sf::Color::Red);
	textPause.Set(font, "- PAUSE -", 300, sf::Color::White);
	textOver.Set(font2, L"\n타이틀로 돌아가려면 Enter를 눌러주세요", 30, sf::Color::White);
	textLevel.Set(font, "1", 30, sf::Color::Green);

	gaugeHp.setFillColor(sf::Color::Red);
	gaugeMaxHp.setFillColor(sf::Color(40, 40, 40, 255));
	exp.setFillColor(sf::Color::Green);
	pauseColor = { 0, 0, 0, 0 };
	pauseRect.setFillColor(pauseColor);

	textScore.SetOutLine(3.f, sf::Color::Black);
	textHiScore.SetOutLine(3.f, sf::Color::Black);
	textAmmo.SetOutLine(3.f, sf::Color::Black);
	textWave.SetOutLine(3.f, sf::Color::Black);
	textZombieCount.SetOutLine(3.f, sf::Color::White);
	textPause.SetOutLine(10.f, sf::Color(0, 0, 0, 240));
	textLevel.SetOutLine(2.f, sf::Color::Black);

	gaugeHpSize = { 300.f,60.f };
	gaugeMaxHp.setSize(gaugeHpSize);
	gaugeHp.setSize(gaugeHpSize);
	exp.setSize({ gaugeHpSize.x ,10 });
	pauseRect.setSize(sf::Vector2f(FRAMEWORK.GetWindowSize()));


	//SetOrigin
	textScore.SetOrigin(Origins::TL);
	textHiScore.SetOrigin(Origins::TR);
	imgAmmoIcon.SetOrigin(Origins::BL);
	textAmmo.SetOrigin(Origins::BL);
	Utils::SetOrigin(gaugeHp, Origins::BL);
	Utils::SetOrigin(gaugeMaxHp, Origins::BL);
	textWave.SetOrigin(Origins::BR);
	textZombieCount.SetOrigin(Origins::BR);
	Utils::SetOrigin(exp, Origins::BL);
	textPause.SetOrigin(Origins::MC);
	Utils::SetOrigin(pauseRect, Origins::TL);
	textOver.SetOrigin(Origins::TC);
	textLevel.SetOrigin(Origins::BR);

	//Top
	float topY = 50.f;
	textScore.SetPosition({ 50.f, topY });
	textHiScore.SetPosition({ referenceResolution.x - 50.f, topY });
	pauseRect.setPosition({ 0, 0 });

	//Middle
	textPause.SetPosition(sf::Vector2f(FRAMEWORK.GetWindowSize()) * 0.5f);
	textOver.SetPosition({ sf::Vector2f(FRAMEWORK.GetWindowSize()).x * 0.5f,textPause.GetGlobalBounds().top+ textPause.GetGlobalBounds().height});

	//Bottom
	float BottomY = referenceResolution.y - 50.f;
	imgAmmoIcon.SetPosition({ 50.f, BottomY + 6.f });
	textAmmo.SetPosition({ 150.f, BottomY });
	gaugeHp.setPosition({ 450.f, BottomY + 6.f });
	gaugeMaxHp.setPosition(gaugeHp.getPosition());
	textWave.SetPosition({ referenceResolution.x - 550.f, BottomY });
	textZombieCount.SetPosition({ referenceResolution.x - 50.f, BottomY });
	exp.setPosition(gaugeHp.getPosition());
	textLevel.SetPosition({445.f,BottomY +3.f});
}

void UIHUD::Release()
{
	GameObject::Release();
}

void UIHUD::Reset()
{
	GameObject::Reset();
}

void UIHUD::Update(float dt)
{
	GameObject::Update(dt);
}

void UIHUD::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
	if (isPause && pauseColor.a < 120)
	{
		pauseColor.a++;
		pauseRect.setFillColor(pauseColor);
	}
	if (isGameOver && pauseColor.a < 220)
	{
		pauseColor.a++;
		pauseRect.setFillColor(pauseColor);
	}
}

void UIHUD::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	textScore.Draw(window);
	textHiScore.Draw(window);
	imgAmmoIcon.Draw(window);
	textAmmo.Draw(window);
	window.draw(gaugeMaxHp);
	window.draw(gaugeHp);
	window.draw(exp);
	textLevel.Draw(window);
	textWave.Draw(window);
	textZombieCount.Draw(window);
	if (isPause)
	{
		window.draw(pauseRect);
		textPause.Draw(window);
	}
	if (isGameOver)
	{
		window.draw(pauseRect);
		textPause.Draw(window);
		textOver.Draw(window);
	}
}

void UIHUD::SetScore(int s)
{
	textScore.SetString(formatScore + std::to_string(s));
}

void UIHUD::SetHiScore(int s)
{
	textHiScore.SetString(formatHiScore + std::to_string(s));
}

void UIHUD::SetAmmo(int current, int total)
{
	textAmmo.SetString(std::to_string(current) + " / " + std::to_string(total));
}

void UIHUD::SetHp(int hp, int max)
{
	float value = max > 0 ? (float)hp / max : 0;
	gaugeHp.setSize({ gaugeHpSize.x * value, gaugeHpSize.y });
}

void UIHUD::SetWave(int w)
{
	textWave.SetString(formatWave + std::to_string(w));
}

void UIHUD::SetZombieCount(int count)
{
	textZombieCount.SetString(formatZombieCount + std::to_string(count));
}

void UIHUD::SetExp(int ex, int max, int level)
{
	float value = max > 0 ? (float)ex / max : 0;
	exp.setSize({ gaugeHpSize.x * value, exp.getSize().y });
	textLevel.SetString(std::to_string(level));
}

void UIHUD::SetPause(bool value)
{
	isPause = value;
	if (value)
	{
		pauseColor.a = 0;
		textPause.SetString("- PAUSE -");
		textPause.SetColor(sf::Color::White);
		textPause.SetOrigin(Origins::MC);
	}
}
void UIHUD::SetGameOver(bool value)
{
	isGameOver = value;
	if (value)
	{
		pauseColor.a = 0;
		textPause.SetString("YOU DIED");
		textPause.SetColor(sf::Color::Red);
		textPause.SetOrigin(Origins::MC);
	}
}

void UIHUD::SetResolution(const sf::Vector2f resolution)
{
}
