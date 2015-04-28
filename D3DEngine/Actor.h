#pragma once
#include "Core.h"
#include "Component.h"

class Actor : public Node
{
public:
	static Actor* Create();
	bool Init();
	~Actor();

	void Update() override;
	void Render() override;

public:
	Transform* transform;
};

