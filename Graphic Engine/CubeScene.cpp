#include "CubeScene.h"

#include "Mesh.h"
#include "Material.h"

CubeScene::CubeScene() { }

CubeScene::~CubeScene() { }

void CubeScene::SetupScene()
{
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

	x = 5.0f;
	offset = 0.1f;
}

void CubeScene::CleanResources()
{

}

void CubeScene::Update(float deltaTime)
{
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

void CubeScene::Render()
{
	m_pRenderer->SetProjectionMatrix(testCamera.GetProjectionMatrix());
	m_pRenderer->SetViewMatrix(testCamera.GetViewMatrix());

	//Render the objects
	for (int i = 0; i < 3500; ++i)
	{
		m_pRenderer->Render(&objArray[i]);
	}
}