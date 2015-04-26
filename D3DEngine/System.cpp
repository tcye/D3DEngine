#include "stdafx.h"
#include "System.h"
#include "Renderer.h"
#include "Platform.h"
#include "Input.h"

bool System::Init()
{
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);

	return Init(true, w, h);
}

bool System::Init(int w, int h)
{
	return Init(false, w, h);
}

bool System::Init(bool fullscreen, int w, int h)
{
	m_input = Input::GetInstance();
	m_platform = Platform::GetInstance();
	m_renderer = Renderer::GetInstance();
	
	if (!m_input->Init())
		return false;

	if (!m_platform->Init(fullscreen, w, h))
		return false;
	
	if (!m_renderer->Init(fullscreen, w, h))
		return false;

	return true;
}

void System::Cleanup()
{
	m_renderer->Release();
	m_platform->Release();
	m_input->Release();
}

void System::Run()
{
	m_platform->RunMessageLoop();
}


