#pragma once

#include <d3d11.h>

#include "Transform.h"

class Mesh;
class Material;

class Object
{
public:
	Object();
	~Object();

	void SetMesh(Mesh* _mesh);
	void SetMaterial(Material* _mesh);

	//Qua cosa deve tornare? Che differenza c'è da averlo pubblico, se non lo metto const?
	GFX::Transform* GetTransform();

	void Render(ID3D11DeviceContext* _context);

private:
	Mesh* m_pMesh;
	Material* m_pMaterial;
	GFX::Transform m_oTransform;
};