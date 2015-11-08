/*
Forse è meglio separare i vertex e i pixel in modo da ridurre il più possibile
le chiamate per settare lo shader da usare! Tanto useranno quasi tutti lo stesso vertex shader
*/

#pragma once

#include <d3d11.h>
#include <wchar.h>

class Material
{
public:
	Material();
	~Material();

	void Initialize(const wchar_t* _MPath, const wchar_t* _texturePath, ID3D11Device* _device);

	void SetActive(ID3D11DeviceContext* _context);

	int GetID() const;

private:
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader*	m_pPixelShader;
	ID3D11InputLayout*	m_pInputLayout;

	ID3D11ShaderResourceView* m_pShaderResource;

	int m_iID;

	static int materialCount;
};