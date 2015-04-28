#include "stdafx.h"
#include "Core.h"


void Ref::Retain()
{
	++m_refCount;
}

void Ref::Release()
{
	--m_refCount;
	if (m_refCount == 0)
		delete this;
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
	for (auto obj : m_objects)
		obj->Release();
	m_objects.clear();
}

Node::~Node()
{
	for (auto child : m_children)
		child->Release();
	m_children.clear();
}

void Node::AddChild(Node* child)
{
	child->Retain();
	m_children.push_back(child);
}

void Node::RemoveChild(Node* child)
{
	std::remove_if(m_children.begin(), m_children.end(), 
		[=](Node* c){
		if (c != child)
			return false;
		child->Release();
		return true;
	});
}

void Node::Update()
{
	for (auto child : m_children)
		child->Update();
}

void Node::Render()
{
	for (auto child : m_children)
		child->Render();
}