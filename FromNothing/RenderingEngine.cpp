#include "RenderingEngine.h"

RenderingEngine::RenderingEngine(HINSTANCE hInstance, int nCmdShow, char * t, UINT w, UINT h, bool fs) :
title(t), width(w), height(h), fullscreen(fs)
{
	windowClass = "WindowClass1";
	createWindowClass(hInstance);
	createWindow(hInstance, nCmdShow);
	InitD3D();
}

RenderingEngine::~RenderingEngine()
{
}

bool RenderingEngine::GetQuitMsg()
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			return true;
	}
	return false;
}

void RenderingEngine::CleanD3D()
{
	swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

												   // close and release all existing COM objects
	zbuffer->Release();
	pLayout->Release();
	pVS->Release();
	pPS->Release();
	pVBuffer->Release();
	pIBuffer->Release();
	pCBuffer->Release();
	pTexture->Release();
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}

void RenderingEngine::SetTitleBar(char * newTitle)
{
	title = newTitle;
	SetWindowText(hWnd, title);
}

void RenderingEngine::ShowFpsInTitle(int fps)
{
	std::string newtitle = std::to_string(fps) + "  |  " + title;
	SetWindowText(hWnd, newtitle.c_str());
}

void RenderingEngine::SetMainCamera(Camera * camera)
{
	MainCamera = camera;
}

void RenderingEngine::RenderIndexedVerts(D3DXMATRIX worldMat, int numIndices, int indexOffset, int vertexOffset)
{
	CBUFFER cBuffer;
	cBuffer.LightVector = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	cBuffer.LightColor = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	cBuffer.AmbientColor = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	cBuffer.Final = worldMat * getViewMatrix() * getProjectionMatrix();
	cBuffer.Rotation = worldMat;

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	devcon->IASetIndexBuffer(pIBuffer, DXGI_FORMAT_R32_UINT, 0);

	// select which primtive type we are using
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw the Hypercraft
	devcon->UpdateSubresource(pCBuffer, 0, 0, &cBuffer, 0, 0);
	devcon->PSSetShaderResources(0, 1, &pTexture);
	devcon->DrawIndexed(numIndices, indexOffset, vertexOffset);
}

void RenderingEngine::SwapBuffers()
{
	swapchain->Present(0, 0);
	Clear();
}

void RenderingEngine::Clear()
{
	devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));
	devcon->ClearDepthStencilView(zbuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

int RenderingEngine::UpdateVertexBuffer(VERTEX * vertices, int numVertices)
{
	D3D11_BOX destRegion;
	destRegion.left = sizeof(VERTEX) * VertCount;
	destRegion.right = destRegion.left + sizeof(VERTEX) * numVertices;
	destRegion.top = 0;
	destRegion.bottom = 1;
	destRegion.front = 0;
	destRegion.back = 1;
	devcon->UpdateSubresource(pVBuffer, 0, &destRegion, vertices, sizeof(VERTEX), 0);
	int offset = VertCount;
	VertCount + numVertices;
	return offset;
}

int RenderingEngine::UpdateIndexBuffer(DWORD * indices, int numIndices)
{
	D3D11_BOX destRegion;
	destRegion.left = sizeof(DWORD) * IdxCount;
	destRegion.right = destRegion.left + sizeof(DWORD) * numIndices;
	destRegion.top = 0;
	destRegion.bottom = 1;
	destRegion.front = 0;
	destRegion.back = 1;
	devcon->UpdateSubresource(pIBuffer, 0, &destRegion, indices, sizeof(DWORD), 0);
	int offset = IdxCount;
	IdxCount + numIndices;
	return offset;
}

void RenderingEngine::createWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = windowClass;

	RegisterClassEx(&wc);
}

void RenderingEngine::createWindow(HINSTANCE hInstance, int nCmdShow)
{
	RECT wr = { 0, 0, width, height };    // set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size
	hWnd = CreateWindowEx(NULL,
		windowClass,    // name of the window class
		title,   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		0,    // x-position of the window
		0,    // y-position of the window
		wr.right - wr.left,    // width of the window
		wr.bottom - wr.top,   // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL
	ShowWindow(hWnd, nCmdShow);
	//msg = { 0 };
}

void RenderingEngine::InitD3D()
{
	InitSwapChain();
	InitDepthBuffer();
	InitRenderTarget();
	InitViewport();
	InitPipeline();
	void InitGraphics(); // temporary
}

void RenderingEngine::InitSwapChain()
{
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                   // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // use 32-bit color
	scd.BufferDesc.Width = width;                   // set the back buffer width
	scd.BufferDesc.Height = height;                 // set the back buffer height
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // how swap chain is to be used
	scd.OutputWindow = hWnd;                               // the window to be used
	scd.SampleDesc.Count = 4;                              // how many multisamples
	scd.Windowed = TRUE;                                   // windowed/full-screen mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // allow full-screen switching

														   // create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon);
}

void RenderingEngine::InitDepthBuffer()
{
	D3D11_TEXTURE2D_DESC texd;
	ZeroMemory(&texd, sizeof(texd));

	texd.Width = width;
	texd.Height = height;
	texd.ArraySize = 1;
	texd.MipLevels = 1;
	texd.SampleDesc.Count = 4;
	texd.Format = DXGI_FORMAT_D32_FLOAT;
	texd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	ID3D11Texture2D *pDepthBuffer;
	dev->CreateTexture2D(&texd, NULL, &pDepthBuffer);
	// create the depth buffer
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	dev->CreateDepthStencilView(pDepthBuffer, &dsvd, &zbuffer);
	pDepthBuffer->Release();
}

void RenderingEngine::InitRenderTarget()
{
	// get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// use the back buffer address to create the render target
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	// set the render target as the back buffer
	devcon->OMSetRenderTargets(1, &backbuffer, zbuffer);
}

void RenderingEngine::InitViewport()
{
	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;    // set the left to 0
	viewport.TopLeftY = 0;    // set the top to 0
	viewport.Width = width;    // set the width to the window's width
	viewport.Height = height;    // set the height to the window's height
	viewport.MinDepth = 0;    // the closest an object can be on the depth buffer is 0.0
	viewport.MaxDepth = 1;    // the farthest an object can be on the depth buffer is 1.0

	devcon->RSSetViewports(1, &viewport);
}

void RenderingEngine::InitPipeline()
{
	InitGraphics();
	InitShaders();
}

void RenderingEngine::InitShaders()
{
	ID3D10Blob *VS, *PS;
	// compile the shaders
	D3DX11CompileFromFile("resources/shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
	D3DX11CompileFromFile("resources/shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

	// create the shader objects
	dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	// set the shader objects
	devcon->VSSetShader(pVS, 0, 0);
	devcon->PSSetShader(pPS, 0, 0);

	// create the input element object
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// use the input element descriptions to create the input layout
	dev->CreateInputLayout(ied, 3, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	devcon->IASetInputLayout(pLayout);
}

void RenderingEngine::InitGraphics()
{
	// create buffers?
	pTexture = createShaderResource("resources/Smiley.png");
	pVBuffer = createVertexBuffer(20000);
	pIBuffer = createIndexBuffer(20000);
	pCBuffer = createConstantBuffer<CBUFFER>();
}

D3DXMATRIX RenderingEngine::getViewMatrix()
{
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView,
		&MainCamera->transform->GetPosition(),    // the camera position
		&MainCamera->transform->GetLookAt(),    // the look-at position
		&MainCamera->transform->GetUp());   // the up direction
	return matView;
}

D3DXMATRIX RenderingEngine::getProjectionMatrix()
{
	D3DXMATRIX matProjection;
	D3DXMatrixPerspectiveFovLH(&matProjection,
		MainCamera->getFov(),                    // field of view
		(float)width / (float)height, // aspect ratio
		0.1f,                                       // near view-plane
		100.0f);
	return matProjection;
}

ID3D11Buffer * RenderingEngine::createVertexBuffer(int size)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX) * size;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ID3D11Buffer* pvb;
	dev->CreateBuffer(&bd, NULL, &pvb);
	return pvb;

	/*
	// copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
	memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // copy the data
	devcon->Unmap(pVBuffer, NULL);*/
}

ID3D11Buffer * RenderingEngine::createIndexBuffer(int size)
{
	// create the index buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(DWORD) * size;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	ID3D11Buffer* pib;
	dev->CreateBuffer(&bd, NULL, &pib);
	return pib;
}

template<typename T>
ID3D11Buffer * RenderingEngine::createConstantBuffer()
{
	ID3D11Buffer* pcb;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(T);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	dev->CreateBuffer(&bd, NULL, &pcb);
	devcon->VSSetConstantBuffers(0, 1, &pcb);
	return pcb;
}

ID3D11ShaderResourceView * RenderingEngine::createShaderResource(char * fileName)
{
	ID3D11ShaderResourceView* srv;
	D3DX11CreateShaderResourceViewFromFile(dev,        // the Direct3D device
		fileName,    // load Wood.png in the local folder
		NULL,           // no additional information
		NULL,           // no multithreading
		&srv,      // address of the shader-resource-view
		NULL);          // no multithreading
	return srv;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

