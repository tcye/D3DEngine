#pragma once
#include "Core.h"

class Input
{
	SINGLETON_CLASS(Input)
	friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
public:
	bool Init();
	void Cleanup();

	bool IsKeyDown(unsigned int key);

private:
	void KeyDown(unsigned int input);
	void KeyUp(unsigned int input);

private:
	bool m_keys[256];
};