#include "stdafx.h"
#include "Renderer.h"
#include "Platform.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

const DWORD Vertex::FVF = D3DFVF_XYZ;

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