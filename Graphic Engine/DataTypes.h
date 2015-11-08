#pragma once

#include <DirectXMath.h>

namespace GFX
{
	struct Vertex
	{
		Vertex(float x, float y, float z, float r, float g, float b, float a, float u, float v)
		{
			position = DirectX::XMFLOAT3(x, y, z);
			color = DirectX::XMFLOAT4(r, g, b, a);
			texCoord = DirectX::XMFLOAT2(u, v);
		}
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT2 texCoord;
	};

	struct ConstantObject
	{
		DirectX::XMMATRIX WVP;
	};
}