#include "RenderingEngine.h"

RenderingEngine::RenderingEngine(HINSTANCE hInstance, int nCmdShow, char * t, UINT w, UINT h, bool fs)
{
}

RenderingEngine::~RenderingEngine()
{
}

bool RenderingEngine::GetQuitMsg()
{
	return false;
}

void RenderingEngine::CleanD3D()
{
}

void RenderingEngine::SetTitleBar(char * newTitle)
{
}

void RenderingEngine::ShowFpsInTitle(int fps)
{
}

void RenderingEngine::SetMainCamera(Camera * camera)
{
}

void RenderingEngine::RenderIndexedVerts(D3DXMATRIX worldMat, int numIndices, int indexOffset, int vertexOffset)
{
}

void RenderingEngine::SwapBuffers()
{
}

void RenderingEngine::Clear()
{
}

int RenderingEngine::UpdateVertexBuffer(VERTEX * vertices, int numVertices)
{
	return 0;
}

int RenderingEngine::UpdateIndexBuffer(DWORD * indices, int numIndices)
{
	return 0;
}

void RenderingEngine::createWindowClass(HINSTANCE hInstance)
{
}

void RenderingEngine::createWindow(HINSTANCE hInstance, int nCmdShow)
{
}

void RenderingEngine::InitD3D()
{
}

void RenderingEngine::InitSwapChain()
{
}

void RenderingEngine::InitDepthBuffer()
{
}

void RenderingEngine::InitRenderTarget()
{
}

void RenderingEngine::InitViewport()
{
}

void RenderingEngine::InitPipeline()
{
}

void RenderingEngine::InitShaders(ID3D10Blob** VS, ID3D10Blob** PS)
{
}

void RenderingEngine::InitGraphics()
{
}

D3DXMATRIX RenderingEngine::getViewMatrix()
{
	return D3DXMATRIX();
}

D3DXMATRIX RenderingEngine::getProjectionMatrix()
{
	return D3DXMATRIX();
}

ID3D11Buffer * RenderingEngine::createVertexBuffer(int size)
{
	return nullptr;
}

ID3D11Buffer * RenderingEngine::createIndexBuffer(int size)
{
	return nullptr;
}

template<typename T>
inline ID3D11Buffer * RenderingEngine::createConstantBuffer()
{
	return NULL;
}

ID3D11ShaderResourceView * RenderingEngine::createShaderResource(char * fileName)
{
	return nullptr;
}



