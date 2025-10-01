#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

// NEEDED INCLUDE(s)
#include "WindowConstants.h"
#include "Camera.h"
#include "OBJLoader.h"
#include "ScreenEntity.h"
#include "Timer.h"
#include "Light.h"
#include "ConstantBuffer.h"

#include <d3dcompiler.h>
// #include <DirectXPackedVector.h>
#include <windows.h>
#include <string>
#include <comdef.h>

// FORWARD DEC(s)
#include "BasicScreen.h"
#include "GJKScreen.h"
#include "SATScreen.h"
#include "EPAScreen.h"
#include "MassAggScreen.h"

#include "imGui/imgui.h" // \\ //
#include "imGui/imgui_impl_win32.h" // \\ // 
#include "imGui/imgui_impl_dx11.h" // \\ //
#include "imGui/ImGuizmo.h"

class ScreenManager
{
private: // PRIVATE VARIABLE(s) (Custom Variables)

	Camera* m_Camera = nullptr;
	ScreenEntity* m_CurrentScreen = nullptr;
	ScreenEntity* m_SavedScreenState = nullptr;
	GameObjectEntity* m_GuizmoObject = nullptr;
	std::map<col_solution_pair, CollisionManifold> m_CollisionSolutionMap;

	// TIME VARIABLE(s)
	Timer* m_Timer = nullptr;
	float m_SimulationTime = 0.0f;
	float m_Accumulator = 0.0f;
	float m_SimpleCount = 0.0f;

	// LIGHT VARIABLE(s)
	Light basicLight;

private: // PRIVATE FUNCTION(s)

	void GuizmoRendering();

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	ScreenManager(ID3D11Device* device);
	~ScreenManager();

	// BASE FUNCTION(s)
	void Process();
	void Showcase(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);
	void GUIShowcase(ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);

	// HELPER FUNCTION(s)
	void PickingTest();
};

#endif

