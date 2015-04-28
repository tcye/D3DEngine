#pragma once
#include "Core.h"

class VertexBuffer;
class IndexBuffer;

class Renderer
{
	SINGLETON_CLASS(Renderer)
public:
	bool Init(bool, int, int);
	void Cleanup();

	void BeginScene();
	void EndScene();
	void Clear();
	void Present();

	bool SetRenderState(D3DRENDERSTATETYPE, DWORD);
	bool SetTransform(D3DTRANSFORMSTATETYPE, const D3DMATRIX*);

	void DrawPrimitive(VertexBuffer*, UINT, UINT);
	void DrawPrimitive(VertexBuffer*);
	void DrawIndexedPrimitive(VertexBuffer*, IndexBuffer*, INT, UINT, UINT, UINT, UINT);
	void DrawIndexedPrimitive(VertexBuffer*, IndexBuffer*);

	IDirect3DDevice9* GetDeviceHandle()
	{
		return m_device;
	}

private:
	IDirect3D9* m_d3d9;
	IDirect3DDevice9* m_device;
};