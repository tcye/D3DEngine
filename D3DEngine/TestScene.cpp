#include "stdafx.h"
#include "TestScene.h"
#include "Actor.h"

TestScene* TestScene::Create()
{
	TestScene* ts = new TestScene();
	ts->AutoRelease();
	if (!ts->Init())
	{
		return NULL;
	}
	return ts;
}

bool TestScene::Init()
{
	return true;
}


