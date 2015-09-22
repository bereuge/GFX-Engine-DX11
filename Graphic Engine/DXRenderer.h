#pragma once

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "DataTypes.h"

class Object;

class DXRenderer
{
public:
	DXRenderer();
	~DXRenderer();

	void InitializeDX(int _screenWidth, int _screenHeight, bool _vsync, HWND _hwnd, bool _fullScreen, float _screenDepth, float _screenNear);
	void Shutdown();

	void SetViewMatrix(const DirectX::XMMATRIX& _viewMat);
	void SetProjectionMatrix(const DirectX::XMMATRIX& _projMat);

	void BeginRender();
	void EndRender();

	void Render(Object* _objToRender);
	//void RenderScene(Object* _objsToRender, int _iNofObjs);

	//Non sarebbe male cavare questi due getter, manteniamo l'utilizzo delle directx solo all'interno del renderer 
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

	DirectX::XMMATRIX m_mView;
	DirectX::XMMATRIX m_mProjection;

	GFX::ConstantObject m_oCObj;
	ID3D11Buffer* m_bConstObj;

	bool m_bVSyncEnabled;
	int m_iVideoCardMemory;
	char m_sVideoCardDescription[128];

	int m_iCurrentMaterialID = -1;
	int m_iCurrentMeshID = -1;
};