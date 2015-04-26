#pragma once

#include "Scene.h"
#include "Actor.h"

class TestScene : public Scene
{
public:
	static TestScene* Create();
	bool Init();
};

class Cube : public Actor
{
public:
	static Cube* Create();
	bool Init();
};