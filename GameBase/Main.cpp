#include <Windows.h>

int main()
{
	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_9_1,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_2,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_2
	};
	m_rc;
	int x = CW_USEDEFAULT;
	int y = CW_USEDEFAULT;

	m_hMenu = NULL;

	int nDefaultWidth = 640;
	int nDefaultHeight = 480;

	bool bGotMsg;
	MSG msg;
	msg.message = WM_NULL;
	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	if (m_hInstance == NULL)
		m_hInstance = (HINSTANCE)GetModuleHandle(NULL);

	HICON hIcon = NULL;
	WCHAR szExePath[MAX_PATH];
	GetModuleFileName(NULL, szExePath, MAX_PATH);

	if (hIcon == NULL)
		hIcon = ExtractIcon(m_hInstance, szExePath, 0);
	//populate wndclass
	WNDCLASS wndClass;
	wndClass.style = CS_DBLCLKS;
	wndClass.lpfnWndProc = MainClass::StaticWindowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon - hIcon;
	wndClass.hCursor - LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = m_windowClassName.c_str();
	//register wndclass with system
	if (!RegisterClass(&wndClass))
	{
		DWORD dwError = GetLastError();
		if (dwError != ERROR_CLASS_ALREADY_EXISTS)
			return HRESULT_FROM_WIN32(dwError);
	}
	//unsure,  I think these are settings
	SetRect(&m_rc, 0, 0, nDefaultWidth, nDefaultHeight);
	AdjustWindowRect(&m_rc, WS_OVERLAPPEDWINDOW, (m_hMenu != NULL) ? true : false);
	//Create the Window
	m_hWnd = CreateWindow(
		m_windowClassName.c_str(),
		L"Cube11",
		WS_OVERLAPPEDWINDOW,
		x, y,
		(m_rc.right - m_rc.left), (m_rc.bottom - m_rc.top),
		0,
		m_hMenu,
		m_hInstance,
		0
	);

	if (m_hWnd == NULL)
	{
		DWORD dwError = GetLastError();
		return HRESULT_FROM_WIN32(dwError);
	}
	//WindowProc Function
	LRESULT CALLBACK MainClass::StaticWindowProc(
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
				HMENU hMenu;
				hMenu = GetMenu(hWnd);
				if (hMenu != NULL)
				{
					DestroyMenu(hMenu);
				}
				DestroyWindow(hWnd);
				UnregisterClass(
					m_windowClassName.c_str(),
					m_hInstance
				);
				return 0;
			}
			case WM_DESTROY:
				PostQuitMessage(0);
			break;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	//Main loop

	while(WM_QUIT != msg.message)
	{
		bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);

		if (bGotMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else
		{
			renderer->Update();

			renderer->Render();

			deviceResources->Present();
		}
	}


}