#include "stdafx.h"
#include "Actor.h"
#include "Renderer.h"

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
	transform = Transform::Create();
	transform->Retain();
	return true;
}

void Actor::Cleanup()
{
	Node::Cleanup();
	transform->Release();
}

void Actor::Update()
{
	Node::Update();

	transform->OnUpdate();
}

void Actor::Render()
{
	Node::Render();
	
	transform->OnRender();
}

Transform* Transform::Create()
{
	Transform* tf = new Transform();
	tf->AutoRelease();
	if (!tf->Init())
		return NULL;
	return tf;
}

bool Transform::Init()
{
	position = D3DXVECTOR3(.0f, .0f, .0f);
	rotation = D3DXVECTOR3(.0f, .0f, .0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	return true;
}

void Transform::OnUpdate()
{

}

void Transform::OnRender()
{
	D3DXMATRIX rx, ry, rz, scaling, move;
	D3DXMatrixRotationX(&rx, rotation.x);
	D3DXMatrixRotationY(&ry, rotation.y);
	D3DXMatrixRotationZ(&rz, rotation.z);
	D3DXMatrixScaling(&scaling, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&move, position.x, position.y, position.z);
	m_tsworld = scaling * rx * ry * rz * move;

	Renderer::GetInstance()->SetTransform(D3DTS_WORLD, &m_tsworld);
}