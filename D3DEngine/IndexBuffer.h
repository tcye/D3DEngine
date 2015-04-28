#pragma once
#include "Core.h"

class IndexBuffer : public Ref
{
public:
	static IndexBuffer* Create(UINT, DWORD usage = 0);
	~IndexBuffer();
	bool Init(UINT, DWORD);
	

	WORD* Lock(UINT offset = 0, UINT size = 0, DWORD flags = 0);
	void Unlock();

	friend class Renderer;
private:
	IDirect3DIndexBuffer9* m_indexBuffer;
	UINT m_count;
};