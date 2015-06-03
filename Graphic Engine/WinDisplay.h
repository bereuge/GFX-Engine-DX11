#pragma once

#include <Windows.h>

class WinDisplay
{
public:
	WinDisplay();
	~WinDisplay();

	void InitializeWindow(char* _appName, int _screenWidth, int _screenHeight, bool _fullScreen);
	void Shutdown();

	HWND GetHandle() const;

private:
	HWND m_hWindow;
	LPCWSTR m_sAppName;
	HINSTANCE m_hInstance;

	int m_iScreenWidth;
	int m_iScreenHeight;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);