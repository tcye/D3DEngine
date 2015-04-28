#include "stdafx.h"
#include "Scene.h"

Scene* Scene::Create()
{
	Scene* s = new Scene();
	if (!s->Init())
		return NULL;
	return s;
}

bool Scene::Init()
{
	return true;
}
