#include "stdafx.h"
#include "Director.h"
#include "Scene.h"
#include "System.h"

bool Director::Init()
{
	m_run = false;
	return true;
}

void Director::Cleanup()
{
	for (size_t i = 0; i < m_scenes.size(); ++i)
	{
		m_scenes[i]->Release();
	}
	m_scenes.clear();
	m_run = false;
}

void Director::Update()
{
	if (m_run && !m_scenes.empty())
		m_scenes.back()->Update();
}

void Director::Render()
{
	if (!m_scenes.empty())
		m_scenes.back()->Render();
}

void Director::PushScene(Scene* s)
{
	s->Retain();
	m_scenes.push_back(s);
}

void Director::PopScene()
{
	if (!m_scenes.empty())
	{
		m_scenes.back()->Release();
		m_scenes.pop_back();
	}
}

void Director::ReplaceScene(Scene* s)
{
	PopScene();
	PushScene(s);
}

void Director::RunWithScene(Scene* s)
{
	PushScene(s);
	m_run = true;
}

void Director::Pause()
{
	m_run = false;
}

void Director::Resume()
{
	m_run = true;
}

int Director::GetWidth()
{
	return System::GetInstance()->m_width;
}

int Director::GetHeight()
{
	return System::GetInstance()->m_height;
}