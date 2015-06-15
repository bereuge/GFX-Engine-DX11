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
	//Setup the constant buffer for the WorldViewProjection matrix
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));

	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.ByteWidth = sizeof(GFX::WVPObject);
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;

	_renderer->GetDevice()->CreateBuffer(&cbDesc, NULL, &m_bWVPMatrix);

	testCamera.SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, -10.0f));

	//Let's initialize the resources
	Mesh* testmesh = new Mesh();
	testmesh->Initialize(_renderer->GetDevice());
	testObj.SetMesh(testmesh);
	Material* testmat = new Material();
	testmat->Initialize(L"Assets/Test.mat", _renderer->GetDevice());
	testObj.SetMaterial(testmat);
}

void Scene::CleanResources()
{
	//DESTROY EVERYTHING!!
}

void Scene::Update()
{

}

void Scene::PreRender()
{

}

void Scene::Render(DXRenderer* _renderer)
{
	GFX::Transform transform;
	transform.SetPosition(2.f, 0.f, 0.f);
	*(testObj.GetTransform()) = transform;
	//Let's set the constant buffer with the WorldViewProjection matrix
	m_oWVP.WVP = DirectX::XMMatrixTranspose(testObj.GetTransform()->GetWorldMatrix() * testCamera.GetViewMatrix() * testCamera.GetProjectionMatrix());
	_renderer->GetDeviceContext()->UpdateSubresource(m_bWVPMatrix, 0, nullptr, &m_oWVP, 0, 0);
	_renderer->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_bWVPMatrix);

	//Render the object
	testObj.Render(_renderer->GetDeviceContext());
}

void Scene::PostRender()
{

}

void Scene::SetSceneManager(SceneManager* _manager)
{
	m_oSceneManager = _manager;
}