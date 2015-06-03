#pragma once

#include <d3d11.h>

class Material
{
public:
	Material();
	~Material();

private:
	ID3D11VertexShader* m_sVertexShader;
	ID3D11PixelShader* m_sPixelShader;

};