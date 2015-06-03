#pragma once

#include "WinDisplay.h"
#include "DXRenderer.h"
#include "SceneManager.h"

class GFXEngine
{
public:
	GFXEngine();
	~GFXEngine();

	void Initialize(char* _appName, int _screenWidth, int _screenHeight, bool _vsync, bool _fullScreen, float _screenDepth, float _screenNear);

	void Run();

private:
	void Render();

	WinDisplay m_oDisplay;
	DXRenderer m_oRenderer;
	SceneManager m_oSceneManager;
	//Renderer m_rRenderer;
	//Scene* m_sCurrentScene;
};