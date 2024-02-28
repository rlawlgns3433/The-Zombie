#include "pch.h"
#include "Framework.h"
#include "UIDebug.h"
#include "Crosshair.h"

void Framework::Init(int width, int height, const std::string& name)
{
	srand(std::time(NULL));

	windowSize.x = width;
	windowSize.y = height;

	window.create(sf::VideoMode(windowSize.x, windowSize.y), name);
	//window.setFramerateLimit(15);
	window.setMouseCursorVisible(false);

	mouse = new Crosshair();
	mouse->Init();

	uiDebug = &UI_DEBUG.Instance();
	uiDebug->Init();

	DT_MGR.Init();
	InputMgr::Init();
	SOUND_MGR.Init();
	SCENE_MGR.Init();
}

void Framework::Do()
{
	while (window.isOpen())
	{
		deltaTime = realDeltaTime = clock.restart();
		deltaTime *= timeScale * isFocus;

		time += deltaTime;
		realTime += realDeltaTime;

		fixedDeltaTime += deltaTime;

		InputMgr::Clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Tab)
				isDebug = !isDebug;
			InputMgr::UpdateEvent(event);
		}
		InputMgr::Update(GetDT());
		SOUND_MGR.Update(GetDT());


		SCENE_MGR.Update(GetDT());
		mouse->Update(GetDT());
		SCENE_MGR.LateUpdate(GetDT());
		mouse->LateUpdate(GetDT());
		if (fixedDeltaTime.asSeconds() >= fixedInterval)
		{
			SCENE_MGR.FixedUpdate(fixedDeltaTime.asSeconds());
			mouse->FixedUpdate(GetDT());
			if (isDebug)
			{
				SCENE_MGR.DebugUpdate(GetDT());
				uiDebug->DebugUpdate(GetDT());
				mouse->DebugUpdate(GetDT());
			}
			fixedDeltaTime = sf::Time::Zero;
		}



		window.clear();
		SCENE_MGR.Draw(window);
		mouse->Draw(window);
		if (isDebug)
		{
			SCENE_MGR.DebugDraw(window);
			uiDebug->DebugDraw(window);
			mouse->DebugDraw(window);
		}

		window.display();
	}
}

void Framework::Release()
{
	SCENE_MGR.Release();
	SOUND_MGR.Release();

	RES_MGR_TEXTURE.UnloadAll();
	RES_MGR_FONT.UnloadAll();
	RES_MGR_SOUND_BUFFER.UnloadAll();
}
