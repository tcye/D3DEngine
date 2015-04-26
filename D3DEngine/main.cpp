// D3DEngine.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "System.h"



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPTSTR lpCmdLine, int nCmdShow)
{
	System* system = System::GetInstance();

	if (!system->Init(800, 600))
	{
		Error("系统初始化失败！");
		return 1;
	}
	system->Run();
	system->Release();

	return 0;
}
