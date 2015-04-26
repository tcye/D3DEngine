#include "stdafx.h"
#include "System.h"
#include "Renderer.h"
#include "Platform.h"
#include "Input.h"
#include "Director.h"

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
	m_width = w;
	m_height = h;
	m_input = Input::GetInstance();
	m_platform = Platform::GetInstance();
	m_renderer = Renderer::GetInstance();
	m_director = Director::GetInstance();
	
	if (!m_input->Init())
		return false;

	if (!m_platform->Init(fullscreen, w, h))
		return false;
	
	if (!m_renderer->Init(fullscreen, w, h))
		return false;

	if (!m_director->Init())
		return false;

	return true;
}

void System::Cleanup()
{
	m_director->Cleanup();
	m_renderer->Cleanup();
	m_platform->Cleanup();
	m_input->Cleanup();
}

void System::Run()
{
	m_platform->RunMessageLoop();
}

void System::Update()
{
	m_director->Update();
}

void System::Render()
{
	m_renderer->Clear();
	m_renderer->BeginScene();

	m_director->Render();

	m_renderer->EndScene();
	m_renderer->Present();
}


