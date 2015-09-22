#include "Object.h"
#include "Mesh.h"
#include "Material.h"

Object::Object() : m_pMesh(nullptr), m_pMaterial(nullptr), m_bRenderable(true)
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

const Mesh* const Object::GetMesh() const
{
	return m_pMesh;
}

void Object::SetMaterial(Material* _material)
{
	m_pMaterial = _material;
}

const Material* const Object::GetMaterial() const
{
	return m_pMaterial;
}

GFX::Transform* Object::GetTransform()
{
	return &m_oTransform;
}

void Object::SetRenderable(bool _toRender)
{
	m_bRenderable = _toRender;
}

void Object::Render(ID3D11DeviceContext* _context, int _lastMaterialUsed, int _lastMeshUsed)
{
	if (m_bRenderable && m_pMaterial)
	{
		if (m_pMaterial->GetID() != _lastMaterialUsed) m_pMaterial->SetActive(_context);
		if (m_pMesh)
		{
			m_pMesh->Render(_context, m_pMesh->GetID() == _lastMeshUsed);
		}
	}
}