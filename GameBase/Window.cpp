#include "Window.h"

Window::Window()
{
		windowClassName = L"Direct3DWindowClass";
		hInstance = NULL;
}

Window::~Window()
{
}

HRESULT Window::createWindow()
{
	//Populate WNDCLASS
	WNDCLASS wndClass;
	wndClass.style = CS_DBLCLKS;
	wndClass.lpfnWndProc = Window::WindowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = NULL;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = (LPCSTR)windowClassName.c_str();
	//Register and check that it's valid
	if (!RegisterClass(&wndClass))
	{
		DWORD dwError = GetLastError();
		if (dwError != ERROR_CLASS_ALREADY_EXISTS)
			return HRESULT_FROM_WIN32(dwError);
	}
	//Create Window
	//set what we want our workable space to be
	SetRect(
		&rect,
		0,0,
		640,480
	);
	//calculate what size the window needs to be for our workable space
	AdjustWindowRect(&rect,
		WS_OVERLAPPEDWINDOW,
		false);
	//Creates the window
	hWnd = CreateWindowEx(
		WS_OVERLAPPEDWINDOW,
		(LPCSTR)windowClassName.c_str(),
		"GameBase",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		(rect.right - rect.left), (rect.bottom - rect.top),
		0,
		0,
		hInstance,
		0
	);
	//tests that the window is valid
	if (hWnd == NULL)
	{
		DWORD dwError = GetLastError();
		return HRESULT_FROM_WIN32(dwError);
	}
}

LRESULT CALLBACK Window::WindowProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
	{
		switch (uMsg)
		{
			case WM_CLOSE:
			{
				DestroyWindow(hWnd);
				UnregisterClass(
					(LPCSTR)windowClassName.c_str(),
					hInstance
				);
				return 0;
			}
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
