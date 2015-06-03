#include "GFXEngine.h"

GFXEngine::GFXEngine() { }

GFXEngine::~GFXEngine() { }

void GFXEngine::Initialize(char* _appName, int _screenWidth, int _screenHeight, bool _vsync, bool _fullScreen, float _screenDepth, float _screenNear)
{
	m_oDisplay.InitializeWindow(_appName, _screenWidth, _screenHeight, _fullScreen);

	m_oRenderer.InitializeDX(_screenWidth, _screenHeight, _vsync, m_oDisplay.GetHandle(), _fullScreen, _screenDepth, _screenNear);
}

void GFXEngine::Run()
{
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
			Render();
		}
	}
}

void GFXEngine::Render()
{
	m_oRenderer.BeginRender();
	Scene* _currScene = m_oSceneManager.GetCurrentScene();
	if (_currScene != nullptr)
	{
		m_oSceneManager.GetCurrentScene()->PreRender();
		m_oSceneManager.GetCurrentScene()->Render();
		m_oSceneManager.GetCurrentScene()->PostRender();
	}
	m_oRenderer.EndRender();
}