#include "WinDisplay.h"
#include <iostream>

/*long __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_DESTROY:
			std::cout << "\ndestroying window\n";
			PostQuitMessage(0);
			return 0L;
		case WM_LBUTTONDOWN:
			std::cout << "\nmouse left button down at (" << LOWORD(lp)
				<< ',' << HIWORD(lp) << ")\n";
			// fall thru
		default:
			std::cout << '.';
			return DefWindowProc(window, msg, wp, lp);
	}
}*/

int main(int argc, char** argv)
{
	WinDisplay window;
	window.InitializeWindow("TODO", 800, 600, false); 
	
	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done)
	{
		//Gestisce il messaggio
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{

		}
	}
	return 0;
}