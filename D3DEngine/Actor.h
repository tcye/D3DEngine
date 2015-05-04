#pragma once
#include <map>
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

	void SetComponent(std::string, Component*);
	Component* GetComponent(std::string);

public:
	std::map<std::string, Component*> m_components;
};

