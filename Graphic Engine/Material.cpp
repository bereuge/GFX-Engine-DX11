#include "Material.h"

#include <d3dcompiler.h>
#include <iostream>

int Material::materialCount = 0;

Material::Material() 
	: m_pPixelShader(nullptr)
	, m_pVertexShader(nullptr)
	, m_pInputLayout(nullptr)
{

}

Material::~Material()
{

}

void Material::Initialize(const wchar_t* _MPath, ID3D11Device* _device)
{
	//First, compile the shaders...

	HRESULT result;

	ID3DBlob* _VSBlob = nullptr;
	ID3DBlob* _VSErrorBlob = nullptr;

	result = D3DCompileFromFile(_MPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_4_0", 0, 0, &_VSBlob, &_VSErrorBlob);
	if (FAILED(result))
	{
		//assert
		std::cout << "Failed to compile Vertex Shader" << std::endl;
	}

	ID3DBlob* _PSBlob = nullptr;
	ID3DBlob* _PSErrorBlob = nullptr;

	result = D3DCompileFromFile(_MPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_4_0", 0, 0, &_PSBlob, &_PSErrorBlob);
	if (FAILED(result))
	{
		//assert
		std::cout << "Failed to compile Pixel Shader" << std::endl;
	}

	//Let's create'em now
	result = _device->CreateVertexShader(_VSBlob->GetBufferPointer(), _VSBlob->GetBufferSize(), nullptr, &m_pVertexShader);
	if (FAILED(result))
	{
		//assert
		std::cout << "Failed to create Vertex Shader" << std::endl;
	}

	result = _device->CreatePixelShader(_PSBlob->GetBufferPointer(), _PSBlob->GetBufferSize(), nullptr, &m_pPixelShader);
	if (FAILED(result))
	{
		//assert
		std::cout << "Failed to create Pixel Shader" << std::endl;
	}

	D3D11_INPUT_ELEMENT_DESC _iInputLayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	result = _device->CreateInputLayout(_iInputLayoutDesc, 2, _VSBlob->GetBufferPointer(), _VSBlob->GetBufferSize(), &m_pInputLayout);
	if (FAILED(result))
	{
		//assert
		std::cout << "Failed to create Input Layout" << std::endl;
	}

	std::cout << "Material created successfully!" << std::endl;

	m_iID = materialCount;
	++materialCount;

	//Cleanup!
	if (_VSBlob) _VSBlob->Release();
	if (_PSBlob) _PSBlob->Release();
	if (_VSErrorBlob) _VSErrorBlob->Release();
	if (_PSErrorBlob) _PSErrorBlob->Release();
}

void Material::SetActive(ID3D11DeviceContext* _context)
{
	_context->IASetInputLayout(m_pInputLayout);
	_context->VSSetShader(m_pVertexShader, nullptr, 0);
	_context->PSSetShader(m_pPixelShader, nullptr, 0);
}

int Material::GetID() const
{
	return m_iID;
}