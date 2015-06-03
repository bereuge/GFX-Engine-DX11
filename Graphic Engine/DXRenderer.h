#pragma once

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <DirectXMath.h>

class DXRenderer
{
public:
	DXRenderer();
	~DXRenderer();

	void InitializeDX(int _screenWidth, int _screenHeight, bool _vsync, HWND _hwnd, bool _fullScreen, float _screenDepth, float _screenNear);
	void Shutdown();

	void BeginRender();
	void EndRender();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

private:
	IDXGISwapChain* m_dSwapChain;
	ID3D11Device* m_dDevice;
	ID3D11DeviceContext* m_dDeviceContext;
	ID3D11RenderTargetView* m_dRenderTargetView;
	ID3D11Texture2D* m_dDepthStencilBuffer;
	ID3D11DepthStencilState* m_dDepthStencilState;
	ID3D11DepthStencilView* m_dDepthStencilView;
	ID3D11RasterizerState* m_dRasterState;

	DirectX::XMMATRIX m_projectionMatrix;
	DirectX::XMMATRIX m_worldMatrix;
	DirectX::XMMATRIX m_orthoMatrix;

	bool m_bVSyncEnabled;
	int m_iVideoCardMemory;
	char m_sVideoCardDescription[128];
};