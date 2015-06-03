#pragma once

#include "SceneManager.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void SetupScene();
	/*virtual*/ void CleanResources();
	virtual void PreRender();
	/*virtual*/ void Render();
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
	//Model m_oModels[]; //or an array of meshes and another for materials?
	//Light m_oLight;
	//Camera m_oCamera;
	//Renderer* m_oRenderer;
};