#pragma once

#include <DirectXMath.h>

namespace GFX
{
	struct Vertex
	{
		Vertex(float x, float y, float z, float r, float g, float b, float a)
		{
			position = DirectX::XMFLOAT3(x, y, z);
			color = DirectX::XMFLOAT4(r, g, b, a);
		}
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
	};

	struct WVPObject
	{
		DirectX::XMMATRIX WVP;
	};
}