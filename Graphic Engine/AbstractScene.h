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
	AbstractScene();
	virtual ~AbstractScene();

	virtual void SetupScene();
	virtual void CleanResources();

	virtual void Update(float deltaTime);

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	void SetRenderer(DXRenderer* _renderer);
	/*
	void AddObject();
	void DeleteObject();
	void AddLight(?);
	void SetupCamera(?);
	*/

	//INPUT??

protected:
	GFX::Camera testCamera;

	DXRenderer* m_pRenderer;

private:
	//Array (o un qualche tipo custom) di obj 
	Object testObj;
	Object testObj2;
	Object objArray[3500];
	float x;
	float offset;
	int sign = 1;
};