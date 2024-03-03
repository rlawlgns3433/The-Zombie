#pragma once
#include "Scene.h"
#include "TextGo.h"

class UICharacterSelect;

class SceneTitle : public Scene
{
protected:
	SceneTitle(const SceneTitle&) = delete;
	SceneTitle(SceneTitle&&) = delete;
	SceneTitle& operator=(const SceneTitle&) = delete;
	SceneTitle& operator=(SceneTitle&&) = delete;

	std::unordered_map<std::string, TextGo*> texts;

	UICharacterSelect* uiCharacterSelect = nullptr;

	bool isMius = true;
	float speed = 0.1f;
	sf::Vector2f scale = {1.f , 1.f};

public:
	SceneTitle(SceneIds id);
	~SceneTitle() override = default;

	void Init() override;
	void Update(float dt) override;
	void Enter() override;

};

