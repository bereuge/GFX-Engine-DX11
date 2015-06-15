#include "Mesh.h"

#include <iostream>

Mesh::Mesh()
{
	m_bVertexBuffer = nullptr;
	m_bIndexBuffer = nullptr;
}

Mesh::~Mesh()
{

}

void Mesh::Initialize(ID3D11Device* _device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set the number of vertices in the vertex array.
	m_iVertexCount = 8;

	// Set the number of indices in the index array.
	m_iIndexCount = 36;

	// Create the vertex array.
	/*vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}*/

	// Create the index array.

	/*GFX::Vertex vertices[] =
	{
		GFX::Vertex(-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		GFX::Vertex(0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
		GFX::Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f),
	};*/
	GFX::Vertex vertices[] =
	{
		GFX::Vertex(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		GFX::Vertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f),
		GFX::Vertex(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
		GFX::Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f),
		GFX::Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f),
		GFX::Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
		GFX::Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f),
		GFX::Vertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
	};

	/*GFX::Vertex* vertices = new GFX::Vertex[m_iVertexCount];

	vertices[0].position = DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertices[0].color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[1].position = DirectX::XMFLOAT3(0.0f, 0.5f, 0.0f);
	vertices[1].color = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = DirectX::XMFLOAT3(0.5f, -0.5f, 0.0f);
	vertices[2].color = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);*/

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(GFX::Vertex)*m_iVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = _device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_bVertexBuffer);
	if (FAILED(result))
	{
		std::cout << "Failed to create vertex buffer" << std::endl;
	}

	/*unsigned long int* indices = new unsigned long int[m_iIndexCount];

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;*/
	unsigned long int indices[] = 
	{
		3, 1, 0,
		2, 1, 3, // Prima faccia cubo

		0, 5, 4,
		1, 5, 0, // Seconda faccia cubo

		3, 4, 7,
		0, 4, 3, // Terza faccia cubo

		1, 6, 5,
		2, 6, 1, // Quarta faccia cubo

		2, 7, 6,
		3, 7, 2, // Quinta faccia cubo

		6, 4, 5,
		7, 4, 6, // Sesta faccia cubo
	};
	
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_iIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = _device->CreateBuffer(&indexBufferDesc, &indexData, &m_bIndexBuffer);
	if (FAILED(result))
	{
		std::cout << "Failed to create index buffer" << std::endl;
	}

	std::cout << "Mesh created successfully!" << std::endl;

	//delete[] indices;
	//delete[] vertices;
}

void Mesh::Shutdown()
{
	m_bVertexBuffer->Release();
	m_bVertexBuffer = nullptr;

	m_bIndexBuffer->Release();
	m_bIndexBuffer = nullptr;
}

void Mesh::Render(ID3D11DeviceContext* _context)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(GFX::Vertex);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	_context->IASetVertexBuffers(0, 1, &m_bVertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	_context->IASetIndexBuffer(m_bIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	_context->DrawIndexed(m_iIndexCount, 0, 0);
}