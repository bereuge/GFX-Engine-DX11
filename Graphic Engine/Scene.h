#pragma once

#include "Object.h"
#include "DXRenderer.h"

class SceneManager;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void SetupScene(DXRenderer* _renderer);
	/*virtual*/ void CleanResources();
	virtual void PreRender();
	/*virtual*/ void Render(DXRenderer* _renderer);
	virtual void PostRender();

	void SetSceneManager(SceneManager* _manager);

	/*
	void AddModel(mesh, material);
	void AddLight(?);
	void SetupCamera(?);
	*/

	//INPUT??

protected:
	SceneManager* m_oSceneManager;

private:
	Object testObj;
	//Model m_oModels[]; //or an array of meshes and another for materials?
	//Light m_oLight;
	//Camera m_oCamera;
	//Renderer* m_oRenderer;
};