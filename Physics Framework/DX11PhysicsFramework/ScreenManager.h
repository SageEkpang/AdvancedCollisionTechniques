#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

// NEEDED INCLUDE(s)
#include "Camera.h"
#include "Structures.h"
#include "OBJLoader.h"
#include "ScreenEntity.h"
#include "Timer.h"
#include "Light.h"
#include "ConstantBuffer.h"
#include <d3dcompiler.h>

//  CUSTOM INCLUDE(s) / FORWARD DEC(s)
class BasicScreen;
class GJKScreen;
class SATScreen;
class MassAggScreen;
class EPAScreen;

class ScreenManager
{
private: // PRIVATE VARIABLE(s) (Application Init Variables)

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

private: // PRIVATE VARIABLE(s) (Custom Variables)

	// WINDOW VARIABLE(s)
	int _WindowWidth = 1280;
	int _WindowHeight = 768;
	Camera* _camera = nullptr;
	ScreenEntity* m_CurrentScreen = nullptr;

	// TIME VARIABLE(s)
	Timer* m_Timer;
	float m_Accumulator = 0.0f;
	float m_SimpleCount = 0.0f;

	// LIGHT VARIABLE(s)
	Light basicLight;

private: // PRIVATE FUNCTION(s)

	HRESULT CreateWindowHandle(HINSTANCE hInstance, int nShowCmd);
	HRESULT CreateSwapChainAndFrameBuffer();
	HRESULT InitGUI();
	HRESULT InitShadersAndInputLayout();
	HRESULT InitPipelineStates();
	HRESULT InitRunTimeData();
	HRESULT CreateD3DDevice();
	HRESULT CreateScreens();

	// NOTE: Object Rendering Functions
	void BeginRendering();
	void EndRendering();

	// NOTE: GUI Rendering Function
	void BeginGUI();
	void ProcessGUI();
	void EndGUI();

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	ScreenManager(HINSTANCE hInstance, int nShowCmd);
	~ScreenManager();

	// BASE FUNCTION(s)
	void Process();
	void Showcase();
	bool HandleKeyboard(MSG msg);

	// HELPER FUNCTION(s)
	void TransitionScreen(PhysicsScreenState state);
};

#endif

