#include "stdafx.h"
#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer* VertexBuffer::Create(UINT count, DWORD usage)
{
	VertexBuffer* buffer = new VertexBuffer();
	buffer->AutoRelease();

	if (!buffer->Init(count, usage))
		return NULL;

	return buffer;
}

bool VertexBuffer::Init(UINT count, DWORD usage)
{
	m_count = count;
	IDirect3DDevice9* device = Renderer::GetInstance()->GetDeviceHandle();
	HRESULT hr = device->CreateVertexBuffer(
		count * sizeof(Vertex),
		usage,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&m_vertexBuffer,
		NULL);
	if (FAILED(hr))
		return false;

	return true;
}

void VertexBuffer::Cleanup()
{
	m_vertexBuffer->Release();
	m_vertexBuffer = NULL;
}

Vertex* VertexBuffer::Lock(UINT offcount, UINT size, DWORD flags)
{
	void* ret;
	HRESULT hr = m_vertexBuffer->Lock(offcount*sizeof(Vertex), size, &ret, flags);

	if (FAILED(hr))
		return NULL;

	return (Vertex*)ret;
}

void VertexBuffer::Unlock()
{
	m_vertexBuffer->Unlock();
}
