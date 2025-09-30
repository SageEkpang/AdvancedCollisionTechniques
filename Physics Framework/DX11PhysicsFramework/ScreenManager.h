#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

// NEEDED INCLUDE(s)
#include "Camera.h"
#include "OBJLoader.h"
#include "ScreenEntity.h"
#include "Timer.h"
#include "Light.h"
#include "ConstantBuffer.h"

#include <d3dcompiler.h>
#include <windows.h>

// FORWARD DEC(s)
#include "BasicScreen.h"
#include "GJKScreen.h"
#include "SATScreen.h"
#include "EPAScreen.h"
#include "MassAggScreen.h"

#include "imGui/imgui.h" // \\ //
#include "imGui/imgui_impl_win32.h" // \\ // 
#include "imGui/imgui_impl_dx11.h" // \\ //

class ScreenManager
{
private: // PRIVATE VARIABLE(s) (Custom Variables)

	Camera* _camera = nullptr;
	ScreenEntity* m_CurrentScreen = nullptr;

	// TIME VARIABLE(s)
	Timer* m_Timer;
	float m_Accumulator = 0.0f;
	float m_SimpleCount = 0.0f;

	// LIGHT VARIABLE(s)
	Light basicLight;

private: // PRIVATE FUNCTION(s)

	// NOTE: Object Rendering Functions
	void BeginRendering();
	void EndRendering();

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	ScreenManager(ID3D11Device* device);
	~ScreenManager();

	// BASE FUNCTION(s)
	void Process();
	void Showcase(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);
	void GUIShowcase();
};

#endif

