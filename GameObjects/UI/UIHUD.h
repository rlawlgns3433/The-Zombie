#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"


class SpriteGo;
class TextGo;

class UIHUD : public GameObject
{
protected:
	int textSize = 60;

	//점수
	TextGo textScore;
	std::string formatScore = "Score: ";
	TextGo textHiScore;
	std::string formatHiScore = "HiScore: ";

	//탄창
	SpriteGo imgAmmoIcon;
	TextGo textAmmo;

	//HP
	sf::RectangleShape gaugeHp;
	sf::RectangleShape gaugeMaxHp;
	sf::Vector2f gaugeHpSize;

	//WAVE
	TextGo textWave;
	std::string formatWave = "Wave: ";

	//좀비
	TextGo textZombieCount;
	std::string formatZombieCount="Zombies: ";

	//비율
	sf::Vector2f referenceResolution = {1920, 1080};
	sf::Vector2f resolution = referenceResolution;

	//경험치
	TextGo textLevel;
	sf::RectangleShape exp;

	//일시정지
	TextGo textPause;
	sf::RectangleShape pauseRect;
	sf::Color pauseColor;
	bool isPause = false;

	//일시정지
	TextGo textOver;
	bool isGameOver = false;

public:
	UIHUD(const std::string& name = "UIHUD");
	~UIHUD() override = default;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;


	void SetScore(int s);
	void SetHiScore(int s);

	void SetAmmo(int current, int total);
	void SetHp(int hp,int max);
	void SetWave(int w);
	void SetZombieCount(int count);
	void SetExp(int ex, int max, int level);

	void SetPause(bool value);
	void SetGameOver(bool value);

	void SetResolution(const sf::Vector2f resolution);
};
