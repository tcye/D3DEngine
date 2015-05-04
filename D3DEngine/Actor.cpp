#include "stdafx.h"
#include "Actor.h"
#include "Renderer.h"

using namespace std;

Actor* Actor::Create()
{
	Actor* actor = new Actor();
	actor->AutoRelease();
	if (!actor->Init())
		return NULL;
	return actor;
}

bool Actor::Init()
{
	return true;
}

Actor::~Actor()
{
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
		it->second->Release();
}

void Actor::SetComponent(string compName, Component* comp)
{
	assert(comp);
	comp->Retain();
	auto it = m_components.find(compName);
	if (it != m_components.end())
		it->second->Release();
	m_components[compName] = comp;
}

Component* Actor::GetComponent(string compName)
{
	auto it = m_components.find(compName);
	if (it == m_components.end())
		return NULL;
	else
		return it->second;
}

void Actor::Update()
{
	Node::Update();

	for (auto it = m_components.begin(); it != m_components.end(); ++it)
		it->second->OnUpdate();
}

void Actor::Render()
{
	Node::Render();
	
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
		it->second->OnRender();
}

