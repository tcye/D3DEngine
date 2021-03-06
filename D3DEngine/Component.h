#pragma once

#include "Core.h"

class Component : public Ref
{
public:
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
};

class Transform : public Component
{
public:
	static Transform* Create();
	bool Init();
	void OnUpdate() override;
	void OnRender() override;
public:
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;
private:
	D3DXMATRIX m_tsworld;
};