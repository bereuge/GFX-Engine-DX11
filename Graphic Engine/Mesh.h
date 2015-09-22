#pragma once

#include <d3d11.h>
#include "DataTypes.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void Initialize(ID3D11Device* _device);
	void Shutdown();

	void LoadFromFile(const char* _filename);

	void Render(ID3D11DeviceContext* _context, bool _alreadyActive);

	int GetID() const;

private:
	ID3D11Buffer* m_bVertexBuffer;
	ID3D11Buffer* m_bIndexBuffer;
	int m_iVertexCount;
	int m_iIndexCount; 
	
	int m_iID;

	static int meshCount;
};