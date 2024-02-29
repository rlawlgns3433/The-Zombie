#include "pch.h"
#include "SceneScore.h"
#include <fstream>
#include <sstream>

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
	GetHigh();

	for (auto ptr : sorted)
	{
		AddGo(ptr);
		std::cout << ptr->GetString() << std::endl;
	}
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


void SceneScore::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneScore::GetHigh()
{
	TextGo* score = nullptr;

	std::ifstream input;
	input.open("highScore.txt");

	if (input.is_open())
	{
		std::stringstream buf;
		buf << input.rdbuf();
		input.close();
		std::string line;
		std::string str;
		int count = 0;
		float y = 0;
		int textSize = 20;
		while (std::getline(buf, line))
		{
			str += line;
			count++;
			if (count == 1)
			{
				int tenCount = 0;
				int ten = std::stoi(line);
				while (ten != 0)
				{
					ten /= 10;
					tenCount++;
				}
				for (int i = 0; i < 10 - tenCount; i++)
				{
					str += " ";
				}
			}
			else if (count == 2)
			{
				score = new TextGo();

				score->Set(RES_MGR_FONT.Get("fonts/DOSIyagiBoldface.ttf"), str, textSize, sf::Color::White);

				score->SetOrigin(Origins::TL);
				score->SetPosition({ 0.f, y });
				y += textSize;
				if (gameObjects.empty())
				{
					gameObjects.push_front(score);
				}
				else
				{
					auto it = gameObjects.begin();
					while (it != gameObjects.end())
					{
						if (score->GetString() < dynamic_cast<TextGo*>(gameObjects.front())->GetString())
						{
							gameObjects.em(it,score);
							break;
						}
						else
						{
							it++;
						}
					}
				}
				str.clear();
				score = nullptr;
				count = 0;
			}
		}
	}
}

