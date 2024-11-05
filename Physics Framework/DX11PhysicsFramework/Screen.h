#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include "Structures.h"

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "DDSTextureLoader.h"
#include "resource.h"
#include "Camera.h"
#include "Structures.h"
#include "OBJLoader.h"

#include <vector>

#include "GameObject.h"

using namespace DirectX;

typedef struct ScreenInformation
{
	PhysicsScreenState physicsScreenState;
	ScreenState screenState;

	ScreenInformation() = default;

	ScreenInformation(PhysicsScreenState physicState, ScreenState screenState)
	{
		this->physicsScreenState = physicState;
		this->screenState = screenState;
	}

} ScreenInfo;

class Screen
{
private:

	int _WindowWidth = 1280;
	int _WindowHeight = 768;

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

	MeshData _objMeshData;
	vector<GameObject*> _gameObjects;

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

private:

	HRESULT CreateWindowHandle(HINSTANCE hInstance, int nShowCmd);
	HRESULT CreateD3DDevice();
	HRESULT CreateSwapChainAndFrameBuffer();
	HRESULT InitShadersAndInputLayout();
	HRESULT InitVertexIndexBuffers();
	HRESULT InitPipelineStates();
	HRESULT InitRunTimeData();

protected:

	std::string m_ScreenName;
	ScreenInformation m_ScreenInformation;

	// Draw / Rendering Functions
	void BeginRendering();
	void EndRendering();

public:

	// CLASS FUNCTION(s)
	/// <summary> Default Constructor for Base Class </summary>
	Screen(std::string screenName);

	/// <summary> Default Destructor for Base Class </summary>
	virtual ~Screen();


	// BASE FUNCTION(s)

	/// <summary> Default Update function for Class </summary>
	virtual void Update(float deltaTime);

	/// <summary> Default Draw function for Class </summary>
	virtual void Draw() { };


	// GETTER FUNCTION(s)
	inline std::string GetName() { return m_ScreenName; }

public:

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	bool HandleKeyboard(MSG msg);

};

#endif
