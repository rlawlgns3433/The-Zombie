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
	title.Set(RES_MGR_FONT.Get("fonts/zombiecontrol.ttf")
		, "RANKING"
		, 150, sf::Color::Black);
	title.SetPosition(sf::Vector2f(textSize, textSize));
	title.SetOutLine(5, sf::Color::White);

	desc.Set(RES_MGR_FONT.Get("fonts/zombiecontrol.ttf")
		, "0"
		, 200, sf::Color::White);
	desc.SetPosition(sf::Vector2f(FRAMEWORK.GetWindowSize().x / 2.f - textSize * 2, textSize + 300));
	desc.SetOutLine(7, sf::Color::Black);
	desc.SetOrigin(Origins::TR);

	back.setTexture(RES_MGR_TEXTURE.Get("graphics/d.png"));
}

void SceneScore::Release()
{
	Scene::Release();

	sorted.clear();
	int currScore = 0;
	float currTime = 0.f;
	bool writeMode = false;

}

void SceneScore::Enter()
{
	Scene::Enter();
	SOUND_MGR.StopBGM();
	GetHigh();
	if (writeMode) { OutHigh(); }
}

void SceneScore::Exit()
{
	Scene::Exit();
	Release();
}

void SceneScore::Update(float dt)
{
	Scene::Update(dt);
	if (InputMgr::GetKeyUp(sf::Keyboard::Escape) || InputMgr::GetKeyUp(sf::Keyboard::Space) || InputMgr::GetKeyUp(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::SceneTitle);
	}


}

void SceneScore::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneScore::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
	if (writeMode && drawScore < currScore)
	{
		drawScore += dt * 1000;
		if (drawScore - drawPreScore >= 150)
		{
			drawPreScore = drawScore;
			SOUND_MGR.PlaySfx("sound/coin07.wav");
		}
		if (drawScore >= currScore)
		{
			drawScore = currScore;
			SOUND_MGR.PlaySfx("sound/coin07.wav");
			if (currIt == sorted.begin())
			{
				title.SetString("New Record!!!");
				title.SetColor(sf::Color::Cyan);
				title.SetOutLine(5.f, sf::Color::Black);
				SOUND_MGR.PlaySfx("sound/hiscore.wav");
			}
		}
		desc.SetString(std::to_string(drawScore));
	}
}


void SceneScore::Draw(sf::RenderWindow& window)
{
	window.draw(back);
	Scene::Draw(window);
	title.Draw(window);
	if (writeMode)
	{
		desc.Draw(window);
	}
}

void SceneScore::OnWriteMode(int score, float time)
{
	writeMode = true;
	currScore = score;
	currTime = time;

}

void SceneScore::GetHigh()
{
	TextGo* textScore = nullptr;

	std::ifstream input;
	input.open("highScore.txt");

	if (!input.is_open()) { return; }

	std::stringstream buf;
	std::string line;

	buf << input.rdbuf();
	input.close();

	int count = 0;
	int score = 0;

	//기록을 가져온다.
	while (std::getline(buf, line))
	{
		count++;
		if (count % 2 == 1) { score = std::stoi(line); }
		else if (count % 2 == 0)
		{
			float time = stof(line);
			if (sorted.empty())
			{
				sorted.push_back(std::make_pair(score, time));
				continue;
			}
			auto it = sorted.begin();
			while (it != sorted.end())
			{
				if (score > it->first)
				{
					sorted.insert(it, std::make_pair(score, time));
					break;
				}
				else if (score == it->first && time < it->second)
				{
					sorted.insert(it, std::make_pair(score, time));
					break;
				}
				else
				{
					it++;
					if (it == sorted.end())
					{
						sorted.insert(it, std::make_pair(score, time));
					}
				}
			}
		}
	}

	//내 점수 기록
	if (writeMode)
	{
		if (sorted.empty())
		{
			sorted.push_back(std::make_pair(currScore, currTime));
			currIt = sorted.begin();
		}
		else
		{
			auto it = sorted.begin();
			while (it != sorted.end())
			{
				if (currScore > it->first)
				{
					currIt = sorted.insert(it, std::make_pair(currScore, currTime));
					break;
				}
				else if (currScore == it->first && currTime < it->second)
				{

					currIt = sorted.insert(it, std::make_pair(currScore, currTime));
					break;
				}
				else
				{
					it++;
					if (it == sorted.end())
					{
						currIt = sorted.insert(it, std::make_pair(currScore, currTime));
					}
				}
			}
		}
	}


	//기록들 AddGo
	std::wstring space;
	float y = textSize;
	auto itScore = sorted.begin();
	while (itScore != sorted.end())
	{
		count = 0;
		space = L"";
		int ten = itScore->second;
		while (ten >= 10)
		{
			ten /= 10;
			count++;
		}
		for (int i = 0; i < 4 - count; i++)
		{
			space += L" ";
		}

		textScore = new TextGo();
		if (writeMode && itScore == currIt)
		{
			textScore->Set(RES_MGR_FONT.Get("fonts/DOSIyagiBoldface.ttf")
				, L"You →   " + std::to_wstring(itScore->first) + L"점 " + space + std::to_wstring(itScore->second) + L"초"
				, textSize, sf::Color::Yellow);
		}
		else
		{
			textScore->Set(RES_MGR_FONT.Get("fonts/DOSIyagiBoldface.ttf")
				, std::to_wstring(itScore->first) + L"점 " + space + std::to_wstring(itScore->second) + L"초"
				, textSize, sf::Color::White);
		}
		textScore->SetOrigin(Origins::TR);
		textScore->SetPosition({ uiView.getSize().x - textSize, y });
		y += textSize;
		AddGo(textScore, Scene::Ui);
		itScore++;
	};

}

void SceneScore::OutHigh()
{
	std::ofstream output;
	output.open("highScore.txt");
	if (output.is_open())
	{
		int count = 0;
		for (auto& pair : sorted)
		{
			count++;
			output << pair.first << '\n' << pair.second << '\n';
			if (count == 10) { break; }
		}
	}
	output.close();

}

