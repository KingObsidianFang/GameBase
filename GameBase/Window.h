#pragma once
#include "Windows.h"
#include <string>


class Window
{
public: 
	Window();
	~Window();
	HRESULT createWindow();
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMSG, WPARAM wParam, LPARAM lParam);
private:
	RECT rect;
	HWND hWnd;
};
static HINSTANCE hInstance;
static std::wstring windowClassName;