#pragma once
#include "Core.h"

class Renderer;
class Platform;
class Input;

class System : public Ref
{
	SINGLETON_CLASS(System)
public:
	bool Init(); // window will be screen
	bool Init(int w, int h); // windows size will be w x h
	void Cleanup() override;
	void Run();

private:
	bool Init(bool fullscreen, int w, int h);
public:
	Input* m_input;
	Platform* m_platform;
	Renderer* m_renderer;
};

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
