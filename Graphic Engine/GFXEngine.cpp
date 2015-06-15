#include "GFXEngine.h"

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
	//Let's setup the first scene
	GetSceneManager().GetCurrentScene()->SetupScene(&m_oRenderer);

	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));

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
			RenderCurrentScene();
		}
	}
}

void GFXEngine::RenderCurrentScene()
{
	m_oRenderer.BeginRender();
	Scene* _currScene = m_oSceneManager.GetCurrentScene();
	if (_currScene != nullptr)
	{
		_currScene->Update();
		_currScene->PreRender();
		_currScene->Render(&m_oRenderer);
		_currScene->PostRender();
	}
	m_oRenderer.EndRender();
}