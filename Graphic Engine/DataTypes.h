#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

namespace GFX
{
	struct Vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
	};
}