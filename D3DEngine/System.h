#pragma once
#include "Core.h"

class Renderer;
class Platform;
class Input;
class Director;

class System
{
	SINGLETON_CLASS(System)
	friend class Director;
public:
	bool Init(); // window will be fullscreen
	bool Init(int w, int h); // windows size will be w x h
	void Cleanup();
	void Run();

	void Update();
	void Render();

private:
	bool Init(bool fullscreen, int w, int h);
public:
	int m_width, m_height;
	Input* m_input;
	Platform* m_platform;
	Renderer* m_renderer;
	Director* m_director;
};

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
