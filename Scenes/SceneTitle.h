#pragma once
#include "Scene.h"
#include "UILevelUp.h"

class SceneTitle : public Scene
{
protected:
	UILevelUp* uiLevelUp;
public:
	SceneTitle(SceneIds id);
	~SceneTitle() override = default;

	void Init() override;
	void Update(float dt) override;
	void Enter() override;

};

