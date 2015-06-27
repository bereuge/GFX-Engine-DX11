#include "Object.h"
#include "Mesh.h"
#include "Material.h"

Object::Object() : m_pMesh(nullptr), m_pMaterial(nullptr)
{

}

Object::~Object()
{
	//to-do
	//Però non dovrebbe essere l'object a fare la delete su mesh e materiale, dovrebbe occuparsene un resource manager!
}

void Object::SetMesh(Mesh* _mesh)
{
	m_pMesh = _mesh;
}

void Object::SetMaterial(Material* _material)
{
	m_pMaterial = _material;
}

GFX::Transform* Object::GetTransform()
{
	return &m_oTransform;
}

void Object::Render(ID3D11DeviceContext* _context)
{
	if (m_pMaterial)
	{
		m_pMaterial->SetActive(_context);
		if (m_pMesh)
		{
			m_pMesh->Render(_context);
		}
	}
}