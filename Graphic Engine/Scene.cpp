#include "Scene.h"

#include "Mesh.h"
#include "Material.h"
#include <iostream>

Scene::Scene()
{
	//Inizializzo qua il renderer? o in setup scene?
}

Scene::~Scene()
{
	//?
}

void Scene::SetupScene(DXRenderer* _renderer)
{
	m_pRenderer = _renderer;
	//Setup the constant buffer for the WorldViewProjection matrix
	/*D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));

	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.ByteWidth = sizeof(GFX::ConstantObject);
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;

	m_pRenderer->GetDevice()->CreateBuffer(&cbDesc, NULL, &m_bWVPMatrix);*/

	testCamera.SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, -10.0f));

	//Let's initialize the resources
	Mesh* testmesh = new Mesh();
	testmesh->Initialize(m_pRenderer->GetDevice());
	testObj.SetMesh(testmesh);
	Material* testmat = new Material();
	testmat->Initialize(L"Assets/Test.mat", m_pRenderer->GetDevice());
	testObj.SetMaterial(testmat);

	testObj2.SetMesh(testmesh);
	testObj2.SetMaterial(testmat);

	testObj.GetTransform()->SetPosition(2.0f, 0.0f, 5.0f);
	testObj.GetTransform()->SetRotationX(60.0f);
	testObj.GetTransform()->SetRotationY(20.0f);
	testObj.GetTransform()->SetRotationZ(5.0f);

	testObj2.GetTransform()->SetPosition(-3.0f, 1.0f, 0.0f);
	testObj2.GetTransform()->SetRotationX(10.0f);
	testObj2.GetTransform()->SetRotationY(50.0f);
	testObj2.GetTransform()->SetRotationZ(1.0f);
	x = 0;
}

void Scene::CleanResources()
{
	//DESTROY EVERYTHING!!
}

void Scene::Update()
{
	x += 0.001f;
	testObj.GetTransform()->SetRotationY(x);
	testObj2.GetTransform()->SetRotationX(-x);
}

void Scene::PreRender()
{

}

void Scene::Render()
{
	m_pRenderer->SetProjectionMatrix(testCamera.GetProjectionMatrix());
	m_pRenderer->SetViewMatrix(testCamera.GetViewMatrix());

	//Render the objects
	m_pRenderer->Render(&testObj);
	m_pRenderer->Render(&testObj2);

}

void Scene::PostRender()
{

}

void Scene::SetSceneManager(SceneManager* _manager)
{
	m_oSceneManager = _manager;
}