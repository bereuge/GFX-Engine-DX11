#include "CubeScene.h"

#include "Mesh.h"
#include "Material.h"

CubeScene::CubeScene() { }

CubeScene::~CubeScene() { }

void CubeScene::SetupScene(DXRenderer* _renderer)
{
	Mesh* mesh = new Mesh();
	mesh->Initialize(_renderer->GetDevice());

	Material* material = new Material();
	material->Initialize(L"Assets/Test.mat", _renderer->GetDevice());

	m_oMainCamera.GetTransform()->SetPosition(0.0f, 0.0f, -10.0f);

	for (int i = 0; i < maxCubes; ++i)
	{
		objArray[i].SetMesh(mesh);
		objArray[i].SetMaterial(material);

		int xpos = rand() % 150 - 75;
		int ypos = rand() % 150 - 75;
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

	for (int i = 0; i < maxCubes; ++i)
	{
		//objArray[i].GetTransform()->SetPosition(objArray[i].GetTransform()->GetPosition().x + (sign * 5 * deltaTime), objArray[i].GetTransform()->GetPosition().y, objArray[i].GetTransform()->GetPosition().z);
	}
}

void CubeScene::PreRender()
{

}

void CubeScene::Render(DXRenderer* _renderer)
{
	_renderer->SetProjectionMatrix(m_oMainCamera.GetProjectionMatrix());
	_renderer->SetViewMatrix(m_oMainCamera.GetViewMatrix());

	//Render the objects
	for (int i = 0; i < maxCubes; ++i)
	{
		_renderer->Render(&objArray[i]);
	}
}

void CubeScene::PostRender()
{

}
