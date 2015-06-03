#pragma once

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

	/*
	void AddModel(mesh, material);
	void AddLight(?);
	void SetupCamera(?);
	*/

	//INPUT??

private:
	//Model m_oModels[]; //or an array of meshes and another for materials?
	//Light m_oLight;
	//Camera m_oCamera;
	//Renderer* m_oRenderer;
};