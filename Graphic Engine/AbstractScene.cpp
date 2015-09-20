#include "AbstractScene.h"

#include "Mesh.h"
#include "Material.h"
#include <iostream>

AbstractScene::AbstractScene()
{
	//Inizializzo qua il renderer? o in setup scene?
}

AbstractScene::~AbstractScene()
{
	//?
}

void AbstractScene::SetupScene()
{
	//Setup the constant buffer for the WorldViewProjection matrix
	/*D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));

	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.ByteWidth = sizeof(GFX::ConstantObject);
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;

	m_pRenderer->GetDevice()->CreateBuffer(&cbDesc, NULL, &m_bWVPMatrix);*/

	Mesh* mesh = new Mesh();
	mesh->Initialize(m_pRenderer->GetDevice());

	Material* material = new Material();
	material->Initialize(L"Assets/Test.mat", m_pRenderer->GetDevice());

	testCamera.SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, -10.0f));

	for (int i = 0; i < 3500; ++i)
	{
		objArray[i].SetMesh(mesh);
		objArray[i].SetMaterial(material);

		int xpos = rand() % 50 - 25;
		int ypos = rand() % 50 - 25;
		int zpos = rand() % 100 + 50;

		objArray[i].GetTransform()->SetPosition(xpos, ypos, zpos);
	}

	//Let's initialize the resources
	/*Mesh* testmesh = new Mesh();
	testmesh->Initialize(m_pRenderer->GetDevice());
	testmesh->LoadFromFile("lol");

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
	testObj2.GetTransform()->SetRotationZ(1.0f);*/
	x = 5.0f;
	offset = 0.1f;
}

void AbstractScene::CleanResources()
{
	//DESTROY EVERYTHING!!
}

void AbstractScene::Update(float deltaTime)
{
	/*x += 0.001f;
	testObj.GetTransform()->SetRotationY(x);
	testObj2.GetTransform()->SetRotationX(-x);*/
	x += offset;
	if (x > 10.0f)
	{
		//x = 0.0f;
		offset = -0.1f;
		sign = -1;
	}

	if (x < 0.0f)
	{
		//x = 0.0f;
		offset = 0.1f;
		sign = 1;
	}

	for (int i = 0; i < 3500; ++i)
	{
		objArray[i].GetTransform()->SetPosition(objArray[i].GetTransform()->GetPosition().x + (sign * 5 * deltaTime), objArray[i].GetTransform()->GetPosition().y, objArray[i].GetTransform()->GetPosition().z);
		//objArray[i].GetTransform()->SetRotationX(1 * deltaTime);
		//objArray[i].GetTransform()->SetRotationY(1 * deltaTime);
	}
}

void AbstractScene::PreRender()
{

}

void AbstractScene::Render()
{
	m_pRenderer->SetProjectionMatrix(testCamera.GetProjectionMatrix());
	m_pRenderer->SetViewMatrix(testCamera.GetViewMatrix());

	//Render the objects
	//m_pRenderer->Render(&testObj);
	//m_pRenderer->Render(&testObj2);
	for (int i = 0; i < 3500; ++i)
	{
		m_pRenderer->Render(&objArray[i]);
	}
}

void AbstractScene::PostRender()
{

}

void AbstractScene::SetRenderer(DXRenderer* _renderer)
{
	m_pRenderer = _renderer;
}