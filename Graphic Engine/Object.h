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
	const Mesh* const GetMesh() const;

	void SetMaterial(Material* _mesh);
	const Material* const GetMaterial() const;

	//Qua cosa deve tornare? Che differenza c'è da averlo pubblico, se non lo metto const?
	GFX::Transform* GetTransform();

	void SetRenderable(bool _toRender);
	bool IsRenderable();

	void Render(ID3D11DeviceContext* _context, int _lastMaterialUsed, int _lastMeshUsed);

private:
	Mesh* m_pMesh;
	Material* m_pMaterial;
	GFX::Transform m_oTransform;

	bool m_bRenderable;
};