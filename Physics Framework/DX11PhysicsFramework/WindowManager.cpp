#include "WindowManager.h"

float WindowManager::m_MouseX = 0;
float WindowManager::m_MouseY = 0;
bool WindowManager::m_MouseButtonLeftDown = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;


	switch (message)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

WindowManager::WindowManager(HINSTANCE hInstance, int nShowCmd)
{
	// NOTE: Initialise Application
	HRESULT t_HR = S_OK;

	try
	{
		t_HR = CreateWindowHandle(hInstance, nShowCmd);
		if (FAILED(t_HR)) throw E_FAIL;

		t_HR = CreateD3DDevice();
		if (FAILED(t_HR)) throw E_FAIL;

		t_HR = CreateSwapChainAndFrameBuffer();
		if (FAILED(t_HR)) throw E_FAIL;

		t_HR = InitShadersAndInputLayout();
		if (FAILED(t_HR)) throw E_FAIL;

		t_HR = InitPipelineStates();
		if (FAILED(t_HR)) throw E_FAIL;

		t_HR = InitRunTimeData();
		if (FAILED(t_HR)) throw E_FAIL;

	}
	catch (...)
	{
		std::runtime_error("One of the Application Creation Functions have failed, E_FAIL");
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(_windowHandle);
	ImGui_ImplDX11_Init(_device, _immediateContext);
	ImGui::StyleColorsClassic();

	ImFont* font_body = io.Fonts->AddFontFromFileTTF("Resources\\Font\\Clofie-Black.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesDefault());
	ImGui::PushFont(font_body);

}

WindowManager::~WindowManager()
{
	Destroy();
	ImGui::PopFont();
}

void WindowManager::Destroy()
{
	if (_immediateContext)_immediateContext->Release();

	if (_frameBufferView)_frameBufferView->Release();
	if (_depthBufferView)_depthBufferView->Release();
	if (_depthStencilBuffer)_depthStencilBuffer->Release();
	if (_swapChain)_swapChain->Release();
	if (_CWcullMode)_CWcullMode->Release();
	if (_CCWcullMode)_CCWcullMode->Release();
	if (_vertexShader)_vertexShader->Release();
	if (_inputLayout)_inputLayout->Release();
	if (_pixelShader)_pixelShader->Release();
	if (_constantBuffer)_constantBuffer->Release();

	if (_DSLessEqual) _DSLessEqual->Release();
	if (_RSCullNone) _RSCullNone->Release();

	if (_samplerLinear)_samplerLinear->Release();

	if (_dxgiDevice)_dxgiDevice->Release();
	if (_dxgiFactory)_dxgiFactory->Release();
	if (_device)_device->Release();
}

HRESULT WindowManager::CreateWindowHandle(HINSTANCE hInstance, int nShowCmd)
{
	const wchar_t* windowName = L"DirectXPhysics";

	WNDCLASSW wndClass;
	wndClass.style = 0;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = 0;
	wndClass.hIcon = 0;
	wndClass.hCursor = 0;
	wndClass.hbrBackground = 0;
	wndClass.lpszMenuName = 0;
	wndClass.lpszClassName = windowName;

	RegisterClassW(&wndClass);
	_windowHandle = CreateWindowExW(0, windowName, windowName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, _WindowWidth, _WindowHeight, nullptr, nullptr, hInstance, nullptr);


	return S_OK;
}

HRESULT WindowManager::CreateD3DDevice()
{
	HRESULT hr = S_OK;

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
	};

	ID3D11Device* baseDevice;
	ID3D11DeviceContext* baseDeviceContext;

	DWORD createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT | createDeviceFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &baseDevice, nullptr, &baseDeviceContext);
	if (FAILED(hr)) return hr;

	///////////////////////////////////////////////////////////////////////////////////////////////

	hr = baseDevice->QueryInterface(__uuidof(ID3D11Device), reinterpret_cast<void**>(&_device));
	hr = baseDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext), reinterpret_cast<void**>(&_immediateContext));

	baseDevice->Release();
	baseDeviceContext->Release();

	///////////////////////////////////////////////////////////////////////////////////////////////

	hr = _device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&_dxgiDevice));
	if (FAILED(hr)) return hr;

	IDXGIAdapter* dxgiAdapter;
	hr = _dxgiDevice->GetAdapter(&dxgiAdapter);
	hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&_dxgiFactory));
	dxgiAdapter->Release();

	return S_OK;
}

HRESULT WindowManager::CreateSwapChainAndFrameBuffer()
{
	HRESULT hr = S_OK;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
	swapChainDesc.Width = 0; // Defer to WindowWidth
	swapChainDesc.Height = 0; // Defer to WindowHeight
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //FLIP* modes don't support sRGB backbuffer
	swapChainDesc.Stereo = FALSE;
	swapChainDesc.SampleDesc.Count = 1; // 1
	swapChainDesc.SampleDesc.Quality = 0; // 0
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.Flags = 0;

	hr = _dxgiFactory->CreateSwapChainForHwnd(_device, _windowHandle, &swapChainDesc, nullptr, nullptr, &_swapChain);
	if (FAILED(hr)) return hr;

	///////////////////////////////////////////////////////////////////////////////////////////////

	ID3D11Texture2D* frameBuffer = nullptr;

	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&frameBuffer));
	if (FAILED(hr)) return hr;

	D3D11_RENDER_TARGET_VIEW_DESC framebufferDesc = {};
	framebufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; //sRGB render target enables hardware gamma correction
	framebufferDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	hr = _device->CreateRenderTargetView(frameBuffer, &framebufferDesc, &_frameBufferView);

	frameBuffer->Release();



	D3D11_TEXTURE2D_DESC depthBufferDesc;
	frameBuffer->GetDesc(&depthBufferDesc); // copy from framebuffer properties

	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = D3D11_USAGE_DEFAULT;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.MiscFlags = 0;

	_device->CreateTexture2D(&depthBufferDesc, nullptr, &_depthStencilBuffer);


	D3D11_DEPTH_STENCIL_VIEW_DESC t_depth_stencil_view_desc;
	ZeroMemory(&t_depth_stencil_view_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	t_depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	t_depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	t_depth_stencil_view_desc.Texture2D.MipSlice = 0;

	_device->CreateDepthStencilView(_depthStencilBuffer, nullptr, &_depthBufferView);

	//UINT a;
	//_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 2, &a);

	return hr;
}

HRESULT WindowManager::InitShadersAndInputLayout()
{
	HRESULT hr = S_OK;
	ID3DBlob* errorBlob;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* vsBlob;

	// Compile the vertex shader
	hr = D3DCompileFromFile(L"SimpleShaders.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS_main", "vs_5_0", dwShaderFlags, 0, &vsBlob, &errorBlob);
	if (FAILED(hr))
	{
		MessageBoxA(_windowHandle, (char*)errorBlob->GetBufferPointer(), nullptr, ERROR);
		errorBlob->Release();
		return hr;
	}

	// Create the vertex shader
	hr = _device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &_vertexShader);

	if (FAILED(hr))
	{
		vsBlob->Release();
		return hr;
	}

	// Compile the pixel shader
	ID3DBlob* psBlob;
	hr = D3DCompileFromFile(L"SimpleShaders.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS_main", "ps_5_0", dwShaderFlags, 0, &psBlob, &errorBlob);
	if (FAILED(hr))
	{
		MessageBoxA(_windowHandle, (char*)errorBlob->GetBufferPointer(), nullptr, ERROR);
		errorBlob->Release();
		return hr;
	}

	// Create the pixel shader
	hr = _device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &_pixelShader);

	if (FAILED(hr))
		return hr;

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// Create the input layout
	hr = _device->CreateInputLayout(inputElementDesc, ARRAYSIZE(inputElementDesc), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &_inputLayout);

	vsBlob->Release();
	psBlob->Release();
	errorBlob->Release();

	return hr;
}

HRESULT WindowManager::InitPipelineStates()
{
	HRESULT hr = S_OK;

	_immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_immediateContext->IASetInputLayout(_inputLayout);

	// Rasterizer

	// CULL NONE Rasterizer
	D3D11_RASTERIZER_DESC cmdesc;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_NONE;
	hr = _device->CreateRasterizerState(&cmdesc, &_RSCullNone);

	// BASE Rasterizer
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_NONE;
	cmdesc.FrontCounterClockwise = true;
	cmdesc.MultisampleEnable = true;
	hr = _device->CreateRasterizerState(&cmdesc, &_CCWcullMode);

	// Clock Wise Rasterizer
	cmdesc.FrontCounterClockwise = false;
	//cmdesc.AntialiasedLineEnable = true;
	hr = _device->CreateRasterizerState(&cmdesc, &_CWcullMode);

	_immediateContext->RSSetState(_CWcullMode);

	// Wireframe Rasterizer
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_WIREFRAME;
	cmdesc.CullMode = D3D11_CULL_NONE;
	cmdesc.FrontCounterClockwise = false;
	hr = _device->CreateRasterizerState(&cmdesc, &m_WireFrameMode);

	D3D11_DEPTH_STENCIL_DESC dssDesc;
	ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dssDesc.DepthEnable = true;
	dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	_device->CreateDepthStencilState(&dssDesc, &_DSLessEqual);

	_immediateContext->OMSetDepthStencilState(_DSLessEqual, 0);

	D3D11_SAMPLER_DESC bilinearSamplerdesc = {};
	bilinearSamplerdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	bilinearSamplerdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	bilinearSamplerdesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	bilinearSamplerdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	bilinearSamplerdesc.MaxLOD = FLT_MAX;
	// bilinearSamplerdesc.MaxLOD = INT_MAX;
	bilinearSamplerdesc.MinLOD = 0;

	hr = _device->CreateSamplerState(&bilinearSamplerdesc, &_samplerLinear);
	if (FAILED(hr)) return hr;




	return S_OK;
}

HRESULT WindowManager::InitRunTimeData()
{
	HRESULT hr = S_OK;

	// Constant Buffer Init
	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	_viewport = { 0.0f, 0.0f, (float)_WindowWidth, (float)_WindowHeight, 0.0f, 1.0f };
	_immediateContext->RSSetViewports(1, &_viewport);

	hr = _device->CreateBuffer(&constantBufferDesc, nullptr, &_constantBuffer);
	if (FAILED(hr)) { return hr; }

	return S_OK;
}

void WindowManager::BeginRendering()
{
	// Clear Buffers
	// float ClearColor[4] = { 0.01f, 0.01f, 0.01f, 1.0f }; // red,green,blue,alpha
	float tempRed = 2.5f;
	float tempGreen = 2.5f;
	float tempBlue = 2.5f;
	float ClearColor[4] = { tempRed / 255.f, tempGreen / 255.f, tempBlue / 255.f, 1.0f }; // red,green,blue,alpha
	_immediateContext->OMSetRenderTargets(1, &_frameBufferView, _depthBufferView);
	_immediateContext->ClearRenderTargetView(_frameBufferView, ClearColor);
	_immediateContext->ClearDepthStencilView(_depthBufferView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Set Up Buffers and Render Scene
	_immediateContext->VSSetShader(_vertexShader, nullptr, 0);
	_immediateContext->PSSetShader(_pixelShader, nullptr, 0);

	_immediateContext->VSSetConstantBuffers(0, 1, &_constantBuffer);
	_immediateContext->PSSetConstantBuffers(0, 1, &_constantBuffer);
	_immediateContext->PSSetSamplers(0, 1, &_samplerLinear);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();
	ImGui::GetCurrentContext();

	ImGuizmo::SetOrthographic(false);
	ImGuizmo::BeginFrame();
}

void WindowManager::EndRendering()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// Present Back Buffer to front
	_swapChain->Present(0, 0);
}

bool WindowManager::HandleEvents(MSG& msg)
{
	switch (msg.message)
	{
		case WM_MOUSEMOVE:
		{
			m_MouseX = LOWORD(msg.lParam);
			m_MouseY = HIWORD(msg.lParam);
		}
		break;

		case WM_LBUTTONDOWN:
		{
			m_MouseButtonLeftDown = true;
		}
		break;

		case WM_LBUTTONUP:
		{
			m_MouseButtonLeftDown = false;
		}
		break;
	}

	return false;
}
