#pragma once
#include "Core.h"

class Platform
{
	SINGLETON_CLASS(Platform)
public:
	bool Init(bool fullscreen, int w, int h);
	void Cleanup();

	void RunMessageLoop();

	HWND GetWindowHandle()
	{
		return m_hwnd;
	}

	HINSTANCE GetInstanceHandle()
	{
		return m_hinstance;
	}

private:
	HINSTANCE m_hinstance;
	HWND m_hwnd;
};