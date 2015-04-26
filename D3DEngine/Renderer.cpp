#include "stdafx.h"
#include "Renderer.h"
#include "Platform.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

const DWORD Vertex::FVF = D3DFVF_XYZ;

static VertexBuffer* vb;
static IndexBuffer* ib;

void Renderer::render()
{
	D3DXMATRIX Rx, Ry;
	D3DXMatrixRotationX(&Rx, 3.14f / 4.0f);

	static float y = 0.0f;
	D3DXMatrixRotationY(&Ry, y);
	y += 0.001f;

	if (y >= 6.28f)
		y = 0.0f;

	D3DMATRIX p = Rx * Ry;
	m_device->SetTransform(D3DTS_WORLD, &p);
	
	DrawIndexedPrimitive(vb, ib);
}

void test()
{
	auto device = Renderer::GetInstance()->GetDeviceHandle();

	vb = VertexBuffer::Create(8);
	vb->retain();
	ib = IndexBuffer::Create(36);
	ib->retain();

	Vertex* vertices = vb->Lock();
	vertices[0] = { -1.0f, -1.0f, -1.0f };
	vertices[1] = { -1.0f, 1.0f, -1.0f };
	vertices[2] = { 1.0f, 1.0f, -1.0f };
	vertices[3] = { 1.0f, -1.0f, -1.0f };
	vertices[4] = { -1.0f, -1.0f, 1.0f };
	vertices[5] = { -1.0f, 1.0f, 1.0f };
	vertices[6] = { 1.0f, 1.0f, 1.0f };
	vertices[7] = { 1.0f, -1.0f, 1.0f };
	vb->Unlock();

	WORD* indices = ib->Lock();
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;

	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;
	ib->Unlock();

	D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	device->SetTransform(D3DTS_VIEW, &V);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI*0.5f, 800.0f / 600.0f, 1.0f, 1000.0f);
	device->SetTransform(D3DTS_PROJECTION, &proj);

	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

bool Renderer::Init(bool fullscreen, int w, int h)
{
	m_d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_d3d9)
		return false;

	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth = w;
	d3dpp.BackBufferHeight = h;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = Platform::GetInstance()->GetWindowHandle();
	d3dpp.Windowed = !fullscreen;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr = m_d3d9->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		d3dpp.hDeviceWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_device);

	if (FAILED(hr))
		return false;

	test();

	return true;
}

void Renderer::Cleanup()
{
	m_device->Release();
	m_device = NULL;

	m_d3d9->Release();
	m_d3d9 = NULL;
}

void Renderer::BeginScene()
{
	m_device->BeginScene();
}

void Renderer::EndScene()
{
	m_device->EndScene();
}

void Renderer::Clear()
{
	m_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 
		0xffffffff, 1.0f, 0);
}

void Renderer::Present()
{
	m_device->Present(NULL, NULL, NULL, NULL);
}

bool Renderer::SetRenderState(D3DRENDERSTATETYPE type, DWORD value)
{
	HRESULT hr = m_device->SetRenderState(type, value);
	if (FAILED(hr))
		return false;
	return true;
}

bool Renderer::SetTransform(D3DTRANSFORMSTATETYPE type, const D3DMATRIX* pMatrix)
{
	HRESULT hr = m_device->SetTransform(type, pMatrix);
	if (FAILED(hr))
		return false;
	return true;
}

void Renderer::DrawPrimitive(VertexBuffer* vbuf, UINT start, UINT count)
{
	m_device->SetStreamSource(0, vbuf->m_vertexBuffer, 0, sizeof(Vertex));
	m_device->SetFVF(Vertex::FVF);
	m_device->DrawPrimitive(D3DPT_TRIANGLELIST, start, count);
}

void Renderer::DrawPrimitive(VertexBuffer* vbuf)
{
	DrawPrimitive(vbuf, 0, vbuf->m_count / 3);
}

void Renderer::DrawIndexedPrimitive(VertexBuffer* vb, IndexBuffer* ib, 
	INT baseVertexIndex, UINT minIndex, UINT numVertices, UINT start, UINT count)
{
	m_device->SetStreamSource(0, vb->m_vertexBuffer, 0, sizeof(Vertex));
	m_device->SetFVF(Vertex::FVF);
	m_device->SetIndices(ib->m_indexBuffer);
	m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, baseVertexIndex,
		minIndex, numVertices, start, count);
}

void Renderer::DrawIndexedPrimitive(VertexBuffer* vb, IndexBuffer* ib)
{
	DrawIndexedPrimitive(vb, ib, 0, 0, vb->m_count, 0, ib->m_count / 3);
}