#pragma once
#include "TextGo.h"
class SceneScore : public Scene
{

protected:
	std::list<TextGo*> scoreList;
	std::list<TextGo*> sorted;

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


	void GetHigh();
};

