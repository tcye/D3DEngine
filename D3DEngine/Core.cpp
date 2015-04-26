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

void Ref::retain()
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