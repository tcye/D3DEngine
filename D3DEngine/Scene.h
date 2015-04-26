#pragma once
#include "Core.h"

class Scene : public Node
{
public:
	static Scene* Create();
	bool Init();
};