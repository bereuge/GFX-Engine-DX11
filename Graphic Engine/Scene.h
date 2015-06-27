#pragma once

#include "DataTypes.h"
#include "Object.h"
#include "Camera.h"
#include "DXRenderer.h"

class SceneManager;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void SetupScene(DXRenderer* _renderer);
	void CleanResources();

	virtual void Update();

	virtual void PreRender();
	void Render();
	virtual void PostRender();

	void SetSceneManager(SceneManager* _manager);

	/*
	void AddObject();
	void DeleteObject();
	void AddLight(?);
	void SetupCamera(?);
	*/

	//INPUT??

protected:
	SceneManager* m_oSceneManager;

private:
	//Array (o un qualche tipo custom) di obj 
	Object testObj;
	Object testObj2;
	float x;

	GFX::Camera testCamera;

	DXRenderer* m_pRenderer;
};