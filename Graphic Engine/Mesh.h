#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void Initialize(ID3D11Device* _device);
	void Shutdown();

	void Render(ID3D11DeviceContext* _context);

private:
	ID3D11Buffer* m_bVertexBuffer;
	ID3D11Buffer* m_bIndexBuffer;
	int m_iVertexCount;
	int m_iIndexCount;
};