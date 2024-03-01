#pragma once
#include "TextGo.h"
class SceneScore : public Scene
{

protected:
	std::list<std::pair<int,float>> sorted;
	int textSize = 60; //점수들 글자 크기

	TextGo title;
	TextGo desc;
	sf::Sprite back;

	float timer = 0.f;

	//기록모드
	bool writeMode = false;
	int drawScore = 0;
	int currScore = 0;
	float currTime = 0.f;
	std::list<std::pair<int, float>>::iterator currIt;

public:
	SceneScore(SceneIds id);
	~SceneScore() override = default;


	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void OnWriteMode(int score, float time);
	void GetHigh();
	void OutHigh();
};

