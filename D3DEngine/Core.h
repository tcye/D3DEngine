#pragma once

#include <vector>

#define SINGLETON_CLASS(T) \
private: \
	T() {} \
	~T() {} \
	T(const T&); \
	const T& operator=(const T&); \
public: \
	static T* GetInstance() \
	{ \
		static T* pInstance = NULL; \
		if (!pInstance) pInstance = new T(); \
		return pInstance; \
	}

#define Warn(msg) MessageBox(NULL, msg, "Warn!", MB_OK)
#define Error(msg) MessageBox(NULL, msg, "Error!", MB_OK)

class Ref
{
public:
	Ref() : m_refCount(1) { }
	virtual ~Ref() { }

	void Retain();
	void Release();
	void AutoRelease();

private:
	int m_refCount;
};

class AutoReleasePool
{
	SINGLETON_CLASS(AutoReleasePool)
public:
	void AddObject(Ref*);
	void Cleanup();

private:
	std::vector<Ref*> m_objects;
};

class Node : public Ref
{
public:
	~Node();

	virtual void Update();
	virtual void Render();

	void AddChild(Node*);
	void RemoveChild(Node*);

protected:
	std::vector<Node*> m_children;

};