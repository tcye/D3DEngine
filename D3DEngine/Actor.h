#pragma once
#include "Core.h"

class Actor : public Node
{
public:
	static Actor* Create();
	bool Init();
	void Cleanup() override;
	
	void Update() override;
	void Render() override;

protected:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_scale;

	D3DXMATRIX m_tsworld;
};