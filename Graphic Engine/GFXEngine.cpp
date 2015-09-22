#include "GFXEngine.h"

#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

GFXEngine::GFXEngine() { }

GFXEngine::~GFXEngine() { }

void GFXEngine::Initialize(char* _appName, int _screenWidth, int _screenHeight, bool _vsync, bool _fullScreen, float _screenDepth, float _screenNear)
{
	m_oDisplay.InitializeWindow(_appName, _screenWidth, _screenHeight, _fullScreen);

	m_oRenderer.InitializeDX(_screenWidth, _screenHeight, _vsync, m_oDisplay.GetHandle(), _fullScreen, _screenDepth, _screenNear);
}

SceneManager& GFXEngine::GetSceneManager()
{
	return m_oSceneManager;
}

void GFXEngine::Run()
{
	//Let's setup the scene
	GetSceneManager().GetCurrentScene()->SetupScene(&m_oRenderer);

	MSG msg;
	bool done;

	ZeroMemory(&msg, sizeof(MSG));

	int fps = 0;
	unsigned long startTime = timeGetTime();
	int frameCount = 0;


	float frameTime = m_oTimer.GetFrameTime();

	done = false;
	while (!done)
	{
		//Gestisce il messaggio
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			++frameCount;
			if (m_oTimer.GetTime() > 1.0f)
			{
				fps = frameCount;
				frameCount = 0;
				m_oTimer.Initialize();
			}

			frameTime = m_oTimer.GetFrameTime();

			std::cout << fps << std::endl;

			RunCurrentScene(frameTime);
		}
	}
}

void GFXEngine::RunCurrentScene(float deltaTime)
{
	m_oRenderer.BeginRender();
	AbstractScene* _currScene = m_oSceneManager.GetCurrentScene();
	if (_currScene != nullptr)
	{
		_currScene->Update(deltaTime);
		_currScene->PreRender();
		_currScene->Render(&m_oRenderer);
		_currScene->PostRender();
	}
	m_oRenderer.EndRender();
}