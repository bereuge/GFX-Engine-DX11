#include "WinDisplay.h"

#include <iostream>

WinDisplay::WinDisplay() : m_iScreenWidth(0), m_iScreenHeight(0) { }

WinDisplay::~WinDisplay() { }

void WinDisplay::InitializeWindow(char* _appName, int _screenWidth, int _screenHeight, bool _fullScreen)
{
	m_iScreenWidth = _screenWidth;
	m_iScreenHeight = _screenHeight;

	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	// Get an external pointer to this object.
	//ApplicationHandle = this;

	// Get the instance of this application.
	m_hInstance = GetModuleHandle(NULL);

	//TODO: set the window title as defined by the user

	// Give the application a name.
	m_sAppName = _appName;

	// Setup the windows class with default settings.
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW /*| CS_OWNDC*/;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(m_hInstance, (LPCTSTR)IDI_APPLICATION);
	wc.hIconSm = LoadIcon(wc.hInstance, (LPCTSTR)IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_sAppName;//m_applicationName;

	// Register the window class.
	if (!RegisterClassEx(&wc))
	{
		//Se non funziona...
	}

	// Determine the resolution of the clients desktop screen.
	//m_iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	//m_iScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (_fullScreen)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)m_iScreenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)m_iScreenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		//screenWidth = 800;
		//screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - m_iScreenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - m_iScreenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hWindow = CreateWindowEx(WS_EX_APPWINDOW, m_sAppName, m_sAppName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, m_iScreenWidth, m_iScreenHeight, NULL, NULL, m_hInstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hWindow, SW_SHOWDEFAULT);
	SetForegroundWindow(m_hWindow);
	SetFocus(m_hWindow);

	std::cout << "Window created successfully." << std::endl;

	// Hide the mouse cursor.
	//ShowCursor(false);
}

void WinDisplay::Shutdown()
{
	ShowCursor(true);

	DestroyWindow(m_hWindow);
	m_hWindow = NULL;

	UnregisterClass(m_sAppName, m_hInstance);
	m_hInstance = NULL;
}

HWND WinDisplay::GetHandle() const
{
	return m_hWindow;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			//return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
			return DefWindowProc(hwnd, umessage, wparam, lparam);
		}
	}
}