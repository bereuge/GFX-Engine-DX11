#pragma once

#include "DataTypes.h"
#include "Object.h"
#include "Camera.h"
#include "DXRenderer.h"
#include <vector>

class SceneManager;

class AbstractScene
{
public:
	virtual void SetupScene(DXRenderer* _renderer) = 0;
	virtual void CleanResources() = 0;

	virtual void Update(float deltaTime) = 0;

	virtual void PreRender() = 0;
	virtual void Render(DXRenderer* _renderer) = 0;
	virtual void PostRender() = 0;
	/*
	void AddObject();
	void DeleteObject();
	void AddLight(?);
	void SetupCamera(?);
	*/

	//INPUT??
};