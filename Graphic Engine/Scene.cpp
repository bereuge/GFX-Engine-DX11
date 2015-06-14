#include "Scene.h"

#include "Mesh.h"
#include "Material.h"
#include <iostream>

Scene::Scene()
{
}

Scene::~Scene()
{
	//?
}

void Scene::SetupScene(DXRenderer* _renderer)
{
	//Let's initialize the resources

	Mesh* testmesh = new Mesh();
	testmesh->Initialize(_renderer->GetDevice());
	testObj.SetMesh(testmesh);
	Material* testmat = new Material();
	testmat->Initialize(L"Assets/TestMaterial.fx", _renderer->GetDevice());
	testObj.SetMaterial(testmat);
}

void Scene::CleanResources()
{
	//DESTROY EVERYTHING!!
}

void Scene::PreRender()
{

}

void Scene::Render(DXRenderer* _renderer)
{
	//Call the renderer
	testObj.Render(_renderer->GetDeviceContext());
}

void Scene::PostRender()
{

}

void Scene::SetSceneManager(SceneManager* _manager)
{
	m_oSceneManager = _manager;
}