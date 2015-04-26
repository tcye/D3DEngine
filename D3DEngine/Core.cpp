#include "stdafx.h"
#include "Core.h"

Ref::Ref() : m_refCount(1)
{

}

Ref::~Ref()
{

}

void Ref::Cleanup()
{

}

void Ref::Retain()
{
	++m_refCount;
}

void Ref::Release()
{
	--m_refCount;
	if (m_refCount == 0)
	{
		Cleanup();
		delete this;
	}
}

void Ref::AutoRelease()
{
	AutoReleasePool::GetInstance()->AddObject(this);
}

void AutoReleasePool::AddObject(Ref* object)
{
	m_objects.push_back(object);
}

void AutoReleasePool::Cleanup()
{
	for (size_t i = 0; i < m_objects.size(); ++i)
	{
		m_objects[i]->Release();
	}
	m_objects.clear();
}

void Node::Cleanup()
{
	for (size_t i = 0; i < m_children.size(); ++i)
	{
		m_children[i]->m_parent = NULL;
		m_children[i]->Release();
	}
	m_children.clear();

	if (m_parent)
		m_parent->RemoveChild(this);
}

void Node::AddChild(Node* child)
{
	child->Retain();
	m_children.push_back(child);
	child->m_parent = this;
}

void Node::RemoveChild(Node* child)
{
	int toRemove = -1;
	for (size_t i = 0; i < m_children.size(); ++i)
	{
		if (m_children[i] == child)
		{
			child->Release();
			toRemove = i;
			break;
		}
	}
	if (toRemove != -1)
		m_children.erase(m_children.begin() + toRemove);
}

void Node::Update()
{
	for (size_t i = 0; i < m_children.size(); ++i)
		m_children[i]->Update();
}

void Node::Render()
{
	for (size_t i = 0; i < m_children.size(); ++i)
		m_children[i]->Update();
}