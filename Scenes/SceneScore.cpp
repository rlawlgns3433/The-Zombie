#include "pch.h"
#include "SceneScore.h"

SceneScore::SceneScore(SceneIds id)
	:Scene(id)
{
}

void SceneScore::Init()
{
	Scene::Init();
	


}

void SceneScore::Release()
{
	Scene::Release();
}

void SceneScore::Enter()
{
	Scene::Enter();
}

void SceneScore::Exit()
{
	Scene::Exit();
}

void SceneScore::Update(float dt)
{
	Scene::Update(dt);
}

void SceneScore::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneScore::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneScore::DebugUpdate(float dt)
{
	Scene::DebugUpdate(dt);
}

void SceneScore::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneScore::DebugDraw(sf::RenderWindow& window)
{
	Scene::DebugDraw(window);
}
