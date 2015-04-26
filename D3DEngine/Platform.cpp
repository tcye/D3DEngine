#include "stdafx.h"
#include "Platform.h"
#include "Input.h"
#include "Renderer.h"

static char szTitle[] = "GameEngine";
static char szWindowClass[] = "GameEngineWndClass";

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		Input::GetInstance()->KeyDown((unsigned int)wParam);
		return 0;

	case WM_KEYUP:
		Input::GetInstance()->KeyUp((unsigned int)wParam);
		return 0;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

bool Platform::Init(bool fullscreen, int w, int h)
{
	m_hinstance = GetModuleHandle(NULL);

	WNDCLASSEX wcex;

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hinstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wcex);

	DWORD dwStyle = WS_VISIBLE;
	if (fullscreen)
		dwStyle |= WS_POPUP;
	else
		dwStyle |= WS_OVERLAPPEDWINDOW;

	m_hwnd = CreateWindow(szWindowClass, szTitle, dwStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL, m_hinstance, NULL);

	if (!m_hwnd)
		return false;

	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);

	return true;
}

void Platform::Cleanup()
{
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	UnregisterClass(szWindowClass, m_hinstance);
	m_hinstance = NULL;
}

void Platform::RunMessageLoop()
{
	MSG msg;
	bool done;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done)
	{
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
			Renderer* renderer = Renderer::GetInstance();
			renderer->Clear();
			renderer->BeginScene();
			
			renderer->render();

			renderer->EndScene();
			renderer->Present();
		}
		AutoReleasePool::GetInstance()->Cleanup();
	}
}