#pragma once
#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

// NEEDED INCLUDE(s)
#include "Camera.h"
#include "Structures.h"
#include "OBJLoader.h"
#include "GameObject.h"
#include "Screen.h"
#include "Timer.h"

//  CUSTOM INCLUDE(s) / FORWARD DEC(s)
class StartUp;
class BasicScreen;
class QuickHullScreen;
class GJKScreen;
class SATScreen;

class ScreenManager
{
private:

	Screen* m_CurrentScreen = nullptr;
	bool m_IsTransitioning;

	PhysicsScreenState m_CurrentPhysicsScreen;

	void Destroy();

private:

	int _WindowWidth = 1280;
	int _WindowHeight = 768;
	Timer* m_Timer;
	float m_Accumulator = 0.0f;

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
	ID3D11Buffer* _cubeVertexBuffer;
	ID3D11Buffer* _cubeIndexBuffer;

	ID3D11Buffer* _planeVertexBuffer;
	ID3D11Buffer* _planeIndexBuffer;

	ID3D11DepthStencilView* _depthBufferView = nullptr;
	ID3D11Texture2D* _depthStencilBuffer = nullptr;

	ID3D11ShaderResourceView* _StoneTextureRV = nullptr;
	ID3D11ShaderResourceView* _GroundTextureRV = nullptr;
	ID3D11ShaderResourceView* _HerculesTextureRV = nullptr;

	ID3D11SamplerState* _samplerLinear = nullptr;

	Light basicLight;

	Camera* _camera = nullptr;
	float _cameraOrbitRadius = 7.0f;
	float _cameraOrbitRadiusMin = 2.0f;
	float _cameraOrbitRadiusMax = 50.0f;
	float _cameraOrbitAngleXZ = -90.0f;
	float _cameraSpeed = 2.0f;

	ConstantBuffer _cbData;

	ID3D11DepthStencilState* _DSLessEqual;
	ID3D11RasterizerState* _RSCullNone;

	ID3D11RasterizerState* _CCWcullMode; //Counter Clockwise
	ID3D11RasterizerState* _CWcullMode; //Clockwise
	ID3D11RasterizerState* m_WireFrameMode; // WireFrame

private:

	HRESULT CreateWindowHandle(HINSTANCE hInstance, int nShowCmd);
	HRESULT CreateSwapChainAndFrameBuffer();
	HRESULT InitShadersAndInputLayout();
	HRESULT InitVertexIndexBuffers();
	HRESULT InitPipelineStates();
	HRESULT InitRunTimeData();
	HRESULT CreateD3DDevice();
	HRESULT CreateScreens();

	void BeginRendering();
	void EndRendering();

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	ScreenManager();

	/// <summary> Default Destructor for Class </summary>
	~ScreenManager();



	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	void Process();

	/// <summary> Default Draw function for Class </summary>
	void Showcase();

	/// <summary> Default Init function for Class </summary>
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	/// <summary> Default Handle Keyboard for Class </summary>
	bool HandleKeyboard(MSG msg);



	// EXTRA FUNCTION(s)

	/// <summary> Transitions Screens either using the Physics Screen State or the Screen State </summary>
	void TransitionScreen(PhysicsScreenState state);
};

#endif

