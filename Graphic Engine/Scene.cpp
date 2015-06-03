#include "Scene.h"

#include <iostream>

Scene::Scene()
{

}

Scene::~Scene()
{
	//?
}

void Scene::SetupScene()
{

}

void Scene::CleanResources()
{
	//DESTROY EVERYTHING!!
}

void Scene::PreRender()
{

}

void Scene::Render()
{
	//Call the renderer
}

void Scene::PostRender()
{

}

void Scene::SetSceneManager(SceneManager* _manager)
{
	m_oSceneManager = _manager;
}