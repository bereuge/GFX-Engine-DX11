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
	/*virtual*/ void CleanResources();

	virtual void Update();

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
	GFX::Camera testCamera;

	GFX::WVPObject m_oWVP;
	ID3D11Buffer* m_bWVPMatrix;
	//Model m_oModels[]; //or an array of meshes and another for materials?
	//Light m_oLight;
	//Camera m_oCamera;
	//Renderer* m_oRenderer;
};