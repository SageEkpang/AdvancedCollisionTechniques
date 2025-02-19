#include "ScreenManager.h"

// FORWARD DEC(s)
#include "BasicScreen.h"
#include "GJKScreen.h"
#include "SATScreen.h"
#include "EPAScreen.h"
#include "MassAggScreen.h"

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

ScreenManager::ScreenManager(HINSTANCE hInstance, int nShowCmd)
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

		t_HR = InitGUI();
		if (FAILED(t_HR)) throw E_FAIL;

		t_HR = InitShadersAndInputLayout();
		if (FAILED(t_HR)) throw E_FAIL;

		t_HR = InitPipelineStates();
		if (FAILED(t_HR)) throw E_FAIL;

		t_HR = InitRunTimeData();
		if (FAILED(t_HR)) throw E_FAIL;

		t_HR = CreateScreens();
		if (FAILED(t_HR)) throw E_FAIL;
	}
	catch (...)
	{
		std::runtime_error("One of the Application Creation Functions have failed, E_FAIL");
	}
}

void ScreenManager::Destroy()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	m_CurrentScreen = nullptr;
	delete m_CurrentScreen;

	delete _camera;
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

ScreenManager::~ScreenManager()
{
	Destroy();
}

HRESULT ScreenManager::CreateScreens()
{
	HRESULT hr = S_OK;

	// Assign Basic Screen to Screen Variable
	m_CurrentScreen = new EPAScreen("GilbertJohnsonKeerthiScreen", _device);

	return S_OK;
}

void ScreenManager::Process()
{
	// NOTE: Accumulator and FrameCounter Variables
	m_SimpleCount += m_Timer->GetDeltaTime();
	m_Accumulator += m_Timer->GetDeltaTime();

	// NOTE: Process Execution
	while (m_Accumulator >= FPS60)
	{
		// Update camera
		_camera->Update(FPS60);

		// Update Screen
		m_CurrentScreen->Update(FPS60);

		m_Accumulator -= FPS60;
	}

	m_Timer->Tick();
}

void ScreenManager::Showcase()
{
	// Begin "Drawing" the content
	BeginRendering();
	BeginGUI();
	ProcessGUI();
	EndGUI();

	// Transpose Matrices and Load Information from Calculated Update function
	// _cbData.World = XMMatrixTranspose(XMLoadFloat4x4(&_camera->GetW));
	_cbData.View = XMMatrixTranspose(XMLoadFloat4x4(&_camera->GetView()));
	_cbData.Projection = XMMatrixTranspose(XMLoadFloat4x4(&_camera->GetProjection()));
	_cbData.EyePosW = _camera->GetPosition();
	_cbData.light = basicLight;

	// Draw the Current Physics Screen
	m_CurrentScreen->Draw(_cbData, _constantBuffer, _immediateContext, _device);

	// End "Drawing" the content
	EndRendering();
}

bool ScreenManager::HandleKeyboard(MSG msg)
{
	// TODO: Move to a GUI Context
	if (GetAsyncKeyState(VK_V))
	{
		_immediateContext->RSSetState(_CWcullMode);
	}
	if (GetAsyncKeyState(VK_C))
	{
		_immediateContext->RSSetState(m_WireFrameMode);
	}

	switch (msg.wParam)
	{
		// RASTERIZER STATE(s)
		// case VK_V: _immediateContext->RSSetState(_CWcullMode); break;
		// case VK_C: _immediateContext->RSSetState(m_WireFrameMode); break;

		// TRANSITION SCREEN(s)
		case VK_0: TransitionScreen(STATE_BASIC_SCREEN); break;
		case VK_1: TransitionScreen(STATE_SAT_SCREEN); break;
		case VK_2: TransitionScreen(STATE_GJK_SCREEN); break;
		case VK_3: TransitionScreen(STATE_EPA_SCREEN); break;
		case VK_4: TransitionScreen(STATE_MASS_ARG_SCREEN); break;
	}

	return false;
}

void ScreenManager::TransitionScreen(PhysicsScreenState state)
{
	// FIXME: Move to GUI and this will work because of order of Update
	m_CurrentScreen = nullptr;
	delete m_CurrentScreen;

	switch (state)
	{
		case PhysicsScreenState::STATE_BASIC_SCREEN: m_CurrentScreen = new BasicScreen("BasicScreen", _device); break;
		case PhysicsScreenState::STATE_SAT_SCREEN: m_CurrentScreen = new SATScreen("SeperateAxisTheorumScreen", _device); break;
		case PhysicsScreenState::STATE_GJK_SCREEN: m_CurrentScreen = new GJKScreen("GilbertJohnsonKeerthiScreen", _device); break;
		case PhysicsScreenState::STATE_EPA_SCREEN: m_CurrentScreen = new EPAScreen("ExpandingPolytopeAlgorithmScreen", _device); break;
		case PhysicsScreenState::STATE_MASS_ARG_SCREEN: m_CurrentScreen = new MassAggScreen("MassAggregateScreen", _device); break;

		default: m_CurrentScreen = new BasicScreen("BasicScreen", _device); break;
	}
}

HRESULT ScreenManager::CreateWindowHandle(HINSTANCE hInstance, int nShowCmd)
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

HRESULT ScreenManager::CreateD3DDevice()
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

HRESULT ScreenManager::CreateSwapChainAndFrameBuffer()
{
	HRESULT hr = S_OK;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
	swapChainDesc.Width = 0; // Defer to WindowWidth
	swapChainDesc.Height = 0; // Defer to WindowHeight
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //FLIP* modes don't support sRGB backbuffer
	swapChainDesc.Stereo = FALSE;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
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

	_device->CreateTexture2D(&depthBufferDesc, nullptr, &_depthStencilBuffer);
	_device->CreateDepthStencilView(_depthStencilBuffer, nullptr, &_depthBufferView);

	return hr;
}

HRESULT ScreenManager::InitGUI()
{
	HRESULT t_HR = S_OK;

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(_windowHandle);
	ImGui_ImplDX11_Init(_device, _immediateContext);

	return S_OK;
}

HRESULT ScreenManager::InitShadersAndInputLayout()
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

HRESULT ScreenManager::InitPipelineStates()
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
	hr = _device->CreateRasterizerState(&cmdesc, &_CCWcullMode);

	// Clock Wise Rasterizer
	cmdesc.FrontCounterClockwise = false;
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
	bilinearSamplerdesc.MaxLOD = INT_MAX;
	bilinearSamplerdesc.MinLOD = 0;

	hr = _device->CreateSamplerState(&bilinearSamplerdesc, &_samplerLinear);
	if (FAILED(hr)) return hr;

	return S_OK;
}

HRESULT ScreenManager::InitRunTimeData()
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

	// Setup Camera
	XMFLOAT3 eye = XMFLOAT3(0.0f, 5.0f, -6.0f);
	XMFLOAT3 at = XMFLOAT3(0.0f, 2.0f, 0.0f);
	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);

	_camera = new Camera(eye, at, up, (float)_WindowWidth, (float)_WindowHeight, 0.01f, 200.0f);

	// Setup the scene's light
	basicLight.AmbientLight = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	basicLight.DiffuseLight = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
	basicLight.SpecularLight = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	basicLight.SpecularPower = 10.0f;
	basicLight.LightVecW = XMFLOAT3(0.0f, 0.5f, -1.0f);

	m_Timer = new Timer();

	return S_OK;
}

void ScreenManager::BeginRendering()
{
	// Clear Buffers
	float ClearColor[4] = { 0.01f, 0.01f, 0.01f, 1.0f }; // red,green,blue,alpha
	_immediateContext->OMSetRenderTargets(1, &_frameBufferView, _depthBufferView);
	_immediateContext->ClearRenderTargetView(_frameBufferView, ClearColor);
	_immediateContext->ClearDepthStencilView(_depthBufferView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Set Up Buffers and Render Scene
	_immediateContext->VSSetShader(_vertexShader, nullptr, 0);
	_immediateContext->PSSetShader(_pixelShader, nullptr, 0);

	_immediateContext->VSSetConstantBuffers(0, 1, &_constantBuffer);
	_immediateContext->PSSetConstantBuffers(0, 1, &_constantBuffer);
	_immediateContext->PSSetSamplers(0, 1, &_samplerLinear);
}

void ScreenManager::EndRendering()
{
	// Present Back Buffer to front
	_swapChain->Present(0, 0);
}

void ScreenManager::BeginGUI()
{
	// ImGui::ShowDebugLogWindow();
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Attribute Window");
	// ImGui::BeginTabBar("General");
}

void ScreenManager::ProcessGUI()
{
	// ImGui::ShowDebugLogWindow();
	ImGui::ShowDebugLogWindow();
	//if (ImGui::BeginTabItem("Post-Process Effects"))
	//{
	//	// NOTE: Depth of Field
	//	ImGui::Text("Activate Depth of Field");

	//	ImGui::EndTabItem();
	//}
}

void ScreenManager::EndGUI()
{
	ImGui::End();
	ImGui::EndFrame();
}
