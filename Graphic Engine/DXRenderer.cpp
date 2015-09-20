#include "DXRenderer.h"

#include "Object.h"
#include <iostream>

DXRenderer::DXRenderer()
{
	m_dSwapChain = nullptr;
	m_dDevice = nullptr;
	m_dDeviceContext = nullptr;
	m_dRenderTargetView = nullptr;
	m_dDepthStencilBuffer = nullptr;
	m_dDepthStencilState = nullptr;
	m_dDepthStencilView = nullptr;
	m_dRasterState = nullptr;
}

DXRenderer::~DXRenderer() 
{ 
	//to-do
}

void DXRenderer::InitializeDX(int _screenWidth, int _screenHeight, bool _vsync, HWND _hwnd, bool _fullScreen, float _screenDepth, float _screenNear)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes, i, numerator = 60, denominator = 1, stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ID3D11Texture2D* backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_VIEWPORT viewport;
	float fieldOfView, screenAspect;

	// Store the vsync setting.
	m_bVSyncEnabled = _vsync;

	// Create a DirectX graphics interface factory.
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))
	{
		//return false;
		std::cout << "Error creating DXGIFactory" << std::endl;
	}

	// Use the factory to create an adapter for the primary graphics interface (video card).
	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
	{
		//return false;
	}

	// Enumerate the primary adapter output (monitor).
	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
	{
		//return false;
	}

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result))
	{
		//return false;
	}

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		//return false;
	}

	// Now fill the display mode list structures.
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))
	{
		//return false;
	}

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	for (i = 0; i<numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)_screenWidth)
		{
			if (displayModeList[i].Height == (unsigned int)_screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	// Get the adapter (video card) description.
	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		//return false;
	}

	// Store the dedicated video card memory in megabytes.
	m_iVideoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);


	// Convert the name of the video card to a character array and store it.
	error = wcstombs_s(&stringLength, m_sVideoCardDescription, 128, adapterDesc.Description, 128);
	if (error != 0)
	{
		//return false;
	}
	std::cout << "Video Card: " << m_sVideoCardDescription << std::endl;

	//Ora si possono liberare tutti gli oggetti e strutture create per ottenere le informazioni sulla scheda video e refresh rate

	// Release the display mode list.
	delete[] displayModeList;
	displayModeList = 0;

	// Release the adapter output.
	adapterOutput->Release();
	adapterOutput = 0;

	// Release the adapter.
	adapter->Release();
	adapter = 0;

	// Release the factory.
	factory->Release();
	factory = 0;

	//Ora inizializziamo DirectX!

	//Initialize the swap chain description.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;

	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = _screenWidth;
	swapChainDesc.BufferDesc.Height = _screenHeight;

	// Set regular 32-bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.
	if (m_bVSyncEnabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	swapChainDesc.OutputWindow = _hwnd;

	// Turn multisampling off.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// Set to full screen or windowed mode.
	if (_fullScreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	//Proviamo senza questa roba avanzata

	// Set the scan line ordering and scaling to unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;



	D3D_FEATURE_LEVEL featureLevel[] =
	{
		// TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling)
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE,
	};

	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	D3D_DRIVER_TYPE g_driverType;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
	{
		// Prova ad inizializzare per i tipi di driver definiti
		g_driverType = driverTypes[driverTypeIndex];

		//result = D3D11CreateDevice(nullptr, g_driverType, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &m_device, nullptr, &m_deviceContext);

		result = D3D11CreateDeviceAndSwapChain(nullptr, g_driverType, nullptr, 0, nullptr, 0,
			D3D11_SDK_VERSION, &swapChainDesc, &m_dSwapChain, &m_dDevice, nullptr, &m_dDeviceContext);

		// Appena funziona esci
		if (SUCCEEDED(result))
			break;
	}

	if (FAILED(result))
	{
		//return false;
		std::cout << "Error creating SwapChain" << std::endl;
	}
	else std::cout << "DirectX SwapChain created successfully." << std::endl;

	//D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	//Creiamo la swapchain, il device e il device context!!
	/*
	result = D3D11CreateDeviceAndSwapChain(
	NULL,
	D3D_DRIVER_TYPE_HARDWARE,
	NULL,
	0,
	featureLevel,
	1,
	D3D11_SDK_VERSION,
	&swapChainDesc,
	&m_swapChain,
	&m_device,
	NULL,
	&m_deviceContext);

	if (FAILED(result))
	{
	return false;
	}
	*/
	// Get the pointer to the back buffer.
	result = m_dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
	if (FAILED(result))
	{
		//return false;
		std::cout << "Error creating backbuffer" << std::endl;
	}

	// Create the render target view with the back buffer pointer.
	result = m_dDevice->CreateRenderTargetView(backBufferPtr, NULL, &m_dRenderTargetView);
	if (FAILED(result))
	{
		//return false;
		std::cout << "Error creating Render Target View" << std::endl;
	}

	// Release pointer to the back buffer as we no longer need it.
	backBufferPtr->Release();
	backBufferPtr = nullptr;


	// Initialize the description of the depth buffer.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = _screenWidth;
	depthBufferDesc.Height = _screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	result = m_dDevice->CreateTexture2D(&depthBufferDesc, NULL, &m_dDepthStencilBuffer);
	if (FAILED(result))
	{
		//return false;
	}

	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	result = m_dDevice->CreateDepthStencilState(&depthStencilDesc, &m_dDepthStencilState);
	if (FAILED(result))
	{
		//return false;
		std::cout << "Error creating Depth Stencil State" << std::endl;
	}

	// Set the depth stencil state.
	m_dDeviceContext->OMSetDepthStencilState(m_dDepthStencilState, 1);

	// Initailze the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	result = m_dDevice->CreateDepthStencilView(m_dDepthStencilBuffer, &depthStencilViewDesc, &m_dDepthStencilView);
	if (FAILED(result))
	{
		//return false;
		std::cout << "Error creating Depth Stencil View" << std::endl;
	}

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	m_dDeviceContext->OMSetRenderTargets(1, &m_dRenderTargetView, m_dDepthStencilView);

	// Setup the raster description which will determine how and what polygons will be drawn.
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	result = m_dDevice->CreateRasterizerState(&rasterDesc, &m_dRasterState);
	if (FAILED(result))
	{
		//return false;
	}

	// Now set the rasterizer state.
	m_dDeviceContext->RSSetState(m_dRasterState);

	// Setup the viewport for rendering.
	viewport.Width = (float)_screenWidth;
	viewport.Height = (float)_screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// Create the viewport.
	m_dDeviceContext->RSSetViewports(1, &viewport);

	// Setup the projection matrix.
	fieldOfView = (float)DirectX::XM_PI / 4.0f;
	screenAspect = (float)_screenWidth / (float)_screenHeight;

	//Create constant buffer for the vertex shader
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));

	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.ByteWidth = sizeof(GFX::ConstantObject);
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;

	m_dDevice->CreateBuffer(&cbDesc, NULL, &m_bConstObj);

	m_dDeviceContext->VSSetConstantBuffers(0, 1, &m_bConstObj);

	std::cout << "DirectX initialized successfully." << std::endl;
}

void DXRenderer::Shutdown()
{
	if (m_dSwapChain)
	{
		m_dSwapChain->SetFullscreenState(false, NULL);
	}

	if (m_dRasterState)
	{
		m_dRasterState->Release();
		m_dRasterState = nullptr;
	}

	if (m_dDepthStencilView)
	{
		m_dDepthStencilView->Release();
		m_dDepthStencilView = nullptr;
	}

	if (m_dDepthStencilState)
	{
		m_dDepthStencilState->Release();
		m_dDepthStencilState = nullptr;
	}

	if (m_dDepthStencilBuffer)
	{
		m_dDepthStencilBuffer->Release();
		m_dDepthStencilBuffer = nullptr;
	}

	if (m_dRenderTargetView)
	{
		m_dRenderTargetView->Release();
		m_dRenderTargetView = nullptr;
	}

	if (m_dDeviceContext)
	{
		m_dDeviceContext->Release();
		m_dDeviceContext = nullptr;
	}

	if (m_dDevice)
	{
		m_dDevice->Release();
		m_dDevice = nullptr;
	}

	if (m_dSwapChain)
	{
		m_dSwapChain->Release();
		m_dSwapChain = nullptr;
	}

}

void DXRenderer::SetViewMatrix(const DirectX::XMMATRIX& _viewMat)
{
	m_mView = _viewMat;
}

void DXRenderer::SetProjectionMatrix(const DirectX::XMMATRIX& _projMat)
{
	m_mProjection = _projMat;
}

void DXRenderer::BeginRender()
{
	float color[4];

	color[0] = 0.1f; //Red
	color[1] = 0.2f; //Green
	color[2] = 0.6f; //Blue
	color[3] = 1.0f; //Alpha

	// Clear the back buffer.
	m_dDeviceContext->ClearRenderTargetView(m_dRenderTargetView, color);

	// Clear the depth buffer.
	m_dDeviceContext->ClearDepthStencilView(m_dDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DXRenderer::EndRender()
{
	if (m_bVSyncEnabled)
	{
		// Lock to screen refresh rate.
		m_dSwapChain->Present(1, 0);
	}
	else
	{
		// Present as fast as possible.
		m_dSwapChain->Present(0, 0);
	}
}

void DXRenderer::Render(Object* _objToRender)
{
	m_oCObj.WVP = DirectX::XMMatrixTranspose(_objToRender->GetTransform()->GetWorldMatrix() * m_mView * m_mProjection);
	m_dDeviceContext->UpdateSubresource(m_bConstObj, 0, nullptr, &m_oCObj, 0, 0);
	_objToRender->Render(m_dDeviceContext);
}

ID3D11Device* DXRenderer::GetDevice()
{
	return m_dDevice;
}

ID3D11DeviceContext* DXRenderer::GetDeviceContext()
{
	return m_dDeviceContext;
}