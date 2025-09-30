#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

// NEEDED INCLUDE(s)
#include "Camera.h"

#include "WindowConstants.h"
#include "OBJLoader.h"
#include "ScreenEntity.h"
#include "Timer.h"
#include "Light.h"
#include "ConstantBuffer.h"

#include <d3dcompiler.h>
#include <windows.h>

#include "imGui/imgui.h"
#include "imGui/imgui_impl_win32.h"
#include "imGui/imgui_impl_dx11.h"
#include "imGui/ImGuizmo.h"

class WindowManager
{
private:

	#pragma region Application Init Variables

	HWND _windowHandle;
	ID3D11DeviceContext* _immediateContext = nullptr;
	ID3D11Device* _device;
	IDXGIDevice* _dxgiDevice = nullptr;
	IDXGIFactory2* _dxgiFactory = nullptr;
	ID3D11RenderTargetView* _frameBufferView = nullptr;
	IDXGISwapChain1* _swapChain;
	D3D11_VIEWPORT _viewport;

	ID3D11VertexShader* _vertexShader;
	ID3D11InputLayout* _inputLayout;
	ID3D11PixelShader* _pixelShader;
	ID3D11Buffer* _constantBuffer;

	ID3D11DepthStencilView* _depthBufferView = nullptr;
	ID3D11Texture2D* _depthStencilBuffer = nullptr;

	ID3D11SamplerState* _samplerLinear = nullptr;

	ConstantBuffer _cbData;

	ID3D11DepthStencilState* _DSLessEqual;
	ID3D11RasterizerState* _RSCullNone;

	// NOTE: Need to create a compute shader and change primitive type after
	ID3D11RasterizerState* _CCWcullMode; //Counter Clockwise
	ID3D11RasterizerState* _CWcullMode; //Clockwise
	ID3D11RasterizerState* m_WireFrameMode; // WireFrame

	#pragma endregion

	void Destroy();

private:

	// WINDOW VARIABLE(s)
	int _WindowWidth = WINDOW_WIDTH;
	int _WindowHeight = WINDOW_HEIGHT;


private:

	HRESULT CreateWindowHandle(HINSTANCE hInstance, int nShowCmd);
	HRESULT CreateSwapChainAndFrameBuffer();
	HRESULT InitShadersAndInputLayout();
	HRESULT InitPipelineStates();
	HRESULT InitRunTimeData();
	HRESULT CreateD3DDevice();


public: // PUBLIC FUNCTION(s)

	static float m_MouseX;
	static float m_MouseY;
	static bool m_MouseButtonLeftDown;

public:

	// CLASS FUNCTION(s)
	WindowManager(HINSTANCE hInstance, int nShowCmd);
	~WindowManager();

	// NOTE: Object Rendering Functions
	void BeginRendering();
	void EndRendering();

	bool HandleEvents(MSG& msg);

	// GETTER FUNCTION(s)
	ConstantBuffer* GetConstantBufferData() { return &_cbData; }
	ID3D11Buffer* GetConstantBuffer() { return _constantBuffer; }
	ID3D11DeviceContext* GetImmediateContext() { return _immediateContext; }
	ID3D11Device* GetDevice() { return _device; }

};

#endif

