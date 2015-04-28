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

Actor::~Actor()
{
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

