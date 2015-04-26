#include "stdafx.h"
#include "IndexBuffer.h"
#include "Renderer.h"


IndexBuffer* IndexBuffer::Create(UINT count, DWORD usage /* = D3DUSAGE_DYNAMIC */)
{
	IndexBuffer* buffer = new IndexBuffer();
	buffer->AutoRelease();

	if (!buffer->Init(count, usage))
		return NULL;

	return buffer;
}

bool IndexBuffer::Init(UINT count, DWORD usage)
{
	m_count = count;
	IDirect3DDevice9* device = Renderer::GetInstance()->GetDeviceHandle();

	HRESULT hr = device->CreateIndexBuffer(
		count * sizeof(WORD),
		usage,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_indexBuffer,
		NULL);

	if (FAILED(hr))
		return false;

	return true;
}

void IndexBuffer::Cleanup()
{
	m_indexBuffer->Release();
	m_indexBuffer = NULL;
}

WORD* IndexBuffer::Lock(UINT offset, UINT size, DWORD flags)
{
	WORD* ret;
	HRESULT hr = m_indexBuffer->Lock(offset * sizeof(WORD), size, (void**)&ret, flags);
	if (FAILED(hr))
		return NULL;
	return ret;
}

void IndexBuffer::Unlock()
{
	m_indexBuffer->Unlock();
}