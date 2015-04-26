// D3DEngine.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "System.h"



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPTSTR lpCmdLine, int nCmdShow)
{
	System* system = System::GetInstance();

	if (!system->Init(800, 600))
	{
		Error("ϵͳ��ʼ��ʧ�ܣ�");
		return 1;
	}
	system->Run();
	system->Release();

	return 0;
}
