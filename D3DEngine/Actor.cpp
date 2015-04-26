#include "stdafx.h"
#include "Actor.h"
#include "Renderer.h"

Actor* Actor::Create()
{
	return NULL;
}

bool Actor::Init()
{
	return true;
}

void Actor::Cleanup()
{
	Node::Cleanup();
}

void Actor::Update()
{
	Node::Update();

	D3DXMATRIX rx, ry, rz, scale, move;
	D3DXMatrixRotationX(&rx, m_rotation.x);
	D3DXMatrixRotationY(&ry, m_rotation.y);
	D3DXMatrixRotationZ(&rz, m_rotation.z);
	D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixTranslation(&move, m_position.x, m_position.y, m_position.z);

	m_tsworld = scale * rx * ry * rz * move;
}

void Actor::Render()
{
	Node::Render();

	Renderer::GetInstance()->SetTransform(D3DTS_WORLD, &m_tsworld);
}