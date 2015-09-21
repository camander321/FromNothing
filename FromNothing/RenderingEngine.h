#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <windowsx.h>
#include <string>

#include <D3D10_1.h>
#include <d3d11.h>
#include <d3dx11.h>

#include "Vertex.h"
#include "MiscUtils.h"
#include "Camera.h"

// include the Direct3D Library file
#pragma comment (lib, "d3dx10.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")

//class Camera;
class RenderingEngine
{
public:
	RenderingEngine(HINSTANCE hInstance, int nCmdShow, char* t, UINT w, UINT h, bool fs);
	~RenderingEngine();
	bool GetQuitMsg();
	void CleanD3D();         // closes Direct3D and releases memory
	void SetTitleBar(char* newTitle);
	void ShowFpsInTitle(int fps);
	void SetMainCamera(Camera* camera);
	void RenderIndexedVerts(D3DXMATRIX worldMat, int numIndices, int indexOffset, int vertexOffset);
	void SwapBuffers();
	void Clear();

	int UpdateVertexBuffer(VERTEX* vertices, int numVertices);
	int UpdateIndexBuffer(DWORD* indices, int numIndices);

private:

	// a struct to define the constant buffer
	struct CBUFFER
	{
		D3DXMATRIX Final;
		D3DXMATRIX Rotation;
		D3DXVECTOR4 LightVector;
		D3DXCOLOR LightColor;
		D3DXCOLOR AmbientColor;
	};

	void createWindowClass(HINSTANCE hInstance);
	void createWindow(HINSTANCE hInstance, int nCmdShow);

	void InitD3D();     // sets up and initializes Direct3D
	void InitSwapChain();
	void InitDepthBuffer();
	void InitRenderTarget();
	void InitViewport();
	void InitPipeline();
	void InitShaders();
	void InitGraphics();

	D3DXMATRIX getViewMatrix();
	D3DXMATRIX getProjectionMatrix();

	ID3D11Buffer* createVertexBuffer(int size);
	ID3D11Buffer* createIndexBuffer(int size);
	template<typename T> ID3D11Buffer* createConstantBuffer();
	ID3D11ShaderResourceView* createShaderResource(char* fileName);

	HWND hWnd;								// the handle for the window, filled by a function

	CBUFFER cBuffer;

	IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
	ID3D11Device *dev;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context
	ID3D11RenderTargetView *backbuffer;    // the pointer to our back buffer
	ID3D11DepthStencilView *zbuffer;       // the pointer to our depth buffer
	ID3D11InputLayout *pLayout;            // the pointer to the input layout
	ID3D11VertexShader *pVS;               // the pointer to the vertex shader
	ID3D11PixelShader *pPS;                // the pointer to the pixel shader
	ID3D11Buffer *pVBuffer;                // the pointer to the vertex buffer
	ID3D11Buffer *pIBuffer;                // the pointer to the index buffer
	ID3D11Buffer *pCBuffer;                // the pointer to the constant buffer
	ID3D11ShaderResourceView *pTexture;    // the pointer to the texture

	int VertCount;
	int IdxCount;

	MSG msg;

	char* title;
	int width;
	int height;
	char* windowClass;
	bool fullscreen;

	Camera* MainCamera;
};

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
