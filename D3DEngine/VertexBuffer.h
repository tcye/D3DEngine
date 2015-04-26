#pragma once
#include "Core.h"

struct Vertex
{
	float x, y, z;
	static const DWORD FVF;
};

class VertexBuffer : public Ref
{
public:
	static VertexBuffer* Create(
		UINT , 
		DWORD usage = 0);


	bool Init(UINT, DWORD);
	void Cleanup() override;

	Vertex* Lock(UINT offset = 0, UINT size = 0, DWORD flags = 0);
	void Unlock();

	friend class Renderer;
private:
	IDirect3DVertexBuffer9* m_vertexBuffer;
	UINT m_count;
};