#pragma once

#include <d3d11.h>

class Mesh;
class Material;

class Object
{
public:
	Object();
	~Object();

	void SetMesh(Mesh* _mesh);
	void SetMaterial(Material* _mesh);

	void Render(ID3D11DeviceContext* _context);

private:
	Mesh* m_pMesh;
	Material* m_pMaterial;
};