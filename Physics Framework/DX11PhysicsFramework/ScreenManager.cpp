#include "ScreenManager.h"
#include "WindowManager.h"

ScreenManager::ScreenManager(ID3D11Device* device)
{
	m_GuizmoObject = new GameObjectEntity();
	// Assign Basic Screen to Screen Variable
	m_CurrentScreen = new BasicScreen("BasicScreen", device);
	m_ScreenState = SCREENS::SCREEN_BASIC;

	// Setup Camera
	XMFLOAT3 eye = XMFLOAT3(0.0f, 10.0f, -15.0f);
	XMFLOAT3 at = XMFLOAT3(0.0f, 2.0f, 0.0f);
	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);

	m_Camera = new Camera(eye, at, up, WINDOW_WIDTH, WINDOW_HEIGHT, 0.01f, 200.0f);

	// Setup the scene's light
	basicLight.AmbientLight = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	basicLight.DiffuseLight = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
	basicLight.SpecularLight = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	basicLight.SpecularPower = 10.0f;
	basicLight.LightVecW = XMFLOAT3(0.0f, 0.5f, -1.0f);

	m_Timer = new Timer();
}

ScreenManager::~ScreenManager()
{
	delete m_CurrentScreen;
	delete m_Camera;
	delete m_Timer;
	m_CollisionSolutionMap.clear();

	if (m_GuizmoObject != nullptr)
	{
		m_GuizmoObject = nullptr;
		delete m_GuizmoObject;
	}
}

void ScreenManager::Process()
{
	// NOTE: Accumulator and FrameCounter Variables
	m_SimpleCount += m_Timer->GetDeltaTime();
	m_Accumulator += m_Timer->GetDeltaTime();

	// NOTE: Process Execution
	while (m_Accumulator >= FPS60)
	{
		auto t_StartClock = high_resolution_clock::now();

		// Update camera
		m_Camera->Update(FPS60);

		// Update Screen
		m_CurrentScreen->Update(FPS60);

		if (WindowManager::m_MouseButtonLeftDown == true) { PickingTest(); }
		if (WindowManager::m_MouseButtonLeftDown == false) { m_GuizmoObject == nullptr; }

		// Get the Current time when the timer is deconstructed
		auto t_EndTimePoint = high_resolution_clock::now();

		// Get the Time in Microseconds since the start of the timer and return the Count of that Time
		auto t_Start = time_point_cast<microseconds>(t_StartClock).time_since_epoch().count();

		// Same with the Start Time but with the EndTimePoint
		auto t_End = time_point_cast<microseconds>(t_EndTimePoint).time_since_epoch().count();

		// Calculate the time taken from start to end (End - Start) (End will always be a higher time)
		auto Duration = t_End - t_Start; // Microseconds
		double ms = Duration * 0.001; // Milliseconds (Microseconds to Milliseconds)

		m_SimulationTime = ms;

		m_Accumulator -= FPS60;
	}

	m_Timer->Tick();
}

void ScreenManager::Showcase(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	if (m_CurrentScreen == nullptr) { return; }
	// Transpose Matrices and Load Information from Calculated Update function
	constantBufferData.View = XMMatrixTranspose(m_Camera->GetViewMatrix());
	constantBufferData.Projection = XMMatrixTranspose(m_Camera->GetProjectionMatrix());
	constantBufferData.EyePosW = m_Camera->GetPosition();
	constantBufferData.light = basicLight;

	// Draw the Current Physics Screen
	m_CurrentScreen->Draw(constantBufferData, constBuff, pImmediateContext, device);
}

void ScreenManager::GuizmoRendering()
{
	if (m_GuizmoObject == nullptr) { return; }

	static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);

	ImGui::Begin("Guizmo");

	if (ImGui::IsKeyPressed(ImGuiKey_1)) { mCurrentGizmoOperation = ImGuizmo::TRANSLATE; }
	if (ImGui::IsKeyPressed(ImGuiKey_2)) { mCurrentGizmoOperation = ImGuizmo::ROTATE; }
	if (ImGui::IsKeyPressed(ImGuiKey_3)) { mCurrentGizmoOperation = ImGuizmo::SCALE; }

	if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE)) { mCurrentGizmoOperation = ImGuizmo::TRANSLATE; }
	ImGui::SameLine();
	if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE)) { mCurrentGizmoOperation = ImGuizmo::ROTATE; }
	ImGui::SameLine();
	if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE)) { mCurrentGizmoOperation = ImGuizmo::SCALE; }

	float* t_WorldMatrix[16] =
	{
		&m_GuizmoObject->GetWorld()->_11, &m_GuizmoObject->GetWorld()->_12, &m_GuizmoObject->GetWorld()->_13, &m_GuizmoObject->GetWorld()->_14,
		&m_GuizmoObject->GetWorld()->_21, &m_GuizmoObject->GetWorld()->_22, &m_GuizmoObject->GetWorld()->_23, &m_GuizmoObject->GetWorld()->_24,
		&m_GuizmoObject->GetWorld()->_31, &m_GuizmoObject->GetWorld()->_32, &m_GuizmoObject->GetWorld()->_33, &m_GuizmoObject->GetWorld()->_34,
		&m_GuizmoObject->GetWorld()->_41, &m_GuizmoObject->GetWorld()->_42, &m_GuizmoObject->GetWorld()->_43, &m_GuizmoObject->GetWorld()->_44,
	};

	if (ImGuizmo::IsUsing())
	{

		float matrixTranslation[3], matrixRotation[3], matrixScale[3];
		ImGuizmo::DecomposeMatrixToComponents(*t_WorldMatrix, matrixTranslation, matrixRotation, matrixScale);

		// m_GuizmoObject->GetComponent<Rigidbody3DObject>()->ApplyForceX();

		m_GuizmoObject->m_Transform.m_Position.x = matrixTranslation[0];
		m_GuizmoObject->m_Transform.m_Position.y = matrixTranslation[1];
		m_GuizmoObject->m_Transform.m_Position.z = matrixTranslation[2];

		m_GuizmoObject->m_Transform.SetRotation(matrixRotation[0], matrixRotation[1], matrixRotation[2]);

		m_GuizmoObject->m_Transform.m_Scale.x = matrixScale[0];
		m_GuizmoObject->m_Transform.m_Scale.y = matrixScale[1];
		m_GuizmoObject->m_Transform.m_Scale.z = matrixScale[2];



		ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, *t_WorldMatrix);
	}

	float t_ViewMatrix[16] = 
	{
		m_Camera->GetView()._11, m_Camera->GetView()._12, m_Camera->GetView()._13, m_Camera->GetView()._14,
		m_Camera->GetView()._21, m_Camera->GetView()._22, m_Camera->GetView()._23, m_Camera->GetView()._24,
		m_Camera->GetView()._31, m_Camera->GetView()._32, m_Camera->GetView()._33, m_Camera->GetView()._34,
		m_Camera->GetView()._41, m_Camera->GetView()._42, m_Camera->GetView()._43, m_Camera->GetView()._44,
	};

	float t_ProjectionMatrix[16] =
	{
		m_Camera->GetProjection()._11, m_Camera->GetProjection()._12, m_Camera->GetProjection()._13, m_Camera->GetProjection()._14,
		m_Camera->GetProjection()._21, m_Camera->GetProjection()._22, m_Camera->GetProjection()._23, m_Camera->GetProjection()._24,
		m_Camera->GetProjection()._31, m_Camera->GetProjection()._32, m_Camera->GetProjection()._33, m_Camera->GetProjection()._34,
		m_Camera->GetProjection()._41, m_Camera->GetProjection()._42, m_Camera->GetProjection()._43, m_Camera->GetProjection()._44,
	};

	ImGuizmo::SetRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	ImGuizmo::Manipulate(t_ViewMatrix, t_ProjectionMatrix, mCurrentGizmoOperation, mCurrentGizmoMode, *t_WorldMatrix, NULL);
	
	ImGui::End();
}

void ScreenManager::GUIShowcase(ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	#pragma region Screen Select

	ImGui::Begin("Scenes");
	if (ImGui::Button("Basic Scene", ImVec2(ImGui::GetWindowWidth() - 15, 20))) { TransitionScreen(SCREENS::SCREEN_BASIC, device); }
	if (ImGui::Button("EPA Scene", ImVec2(ImGui::GetWindowWidth() - 15, 20))) { TransitionScreen(SCREENS::SCREEN_EPA, device); }
	if (ImGui::Button("GJK Scene", ImVec2(ImGui::GetWindowWidth() - 15, 20))) { TransitionScreen(SCREENS::SCREEN_GJK, device); }
	if (ImGui::Button("MassAgg Scene", ImVec2(ImGui::GetWindowWidth() - 15, 20))) { TransitionScreen(SCREENS::SCREEN_MASS_AGG, device); }
	if (ImGui::Button("SAT Scene", ImVec2(ImGui::GetWindowWidth() - 15, 20))) { TransitionScreen(SCREENS::SCREEN_SAT, device); }
	ImGui::End();

	#pragma endregion
	 
	ImGui::Begin("General Window");
	
	ImGui::SeparatorText("Scene Attributes");
	ImGui::Spacing();

	if (ImGui::Button("Reset Scene", ImVec2(ImGui::GetWindowWidth() - 15, 30))) { TransitionScreen(m_ScreenState, device); }

	ImGui::Spacing();
	ImGui::SeparatorText("Rendering Attributes");
	ImGui::Spacing();

	ImGui::Checkbox("Wireframe", &Mesh::m_IsWireFrame);
	ImGui::Checkbox("Mesh", &Mesh::m_RenderMesh);
	ImGui::Checkbox("Collider", &ColliderEntity::m_RenderCollision);
	ImGui::Checkbox("Points", &MassAggregate::m_RenderPoints);

	ImGui::Spacing();
	ImGui::SeparatorText("Force Attributes");
	ImGui::Spacing();

	ImGui::Checkbox("Simulate Gravity: ", &PhysicsEntity::m_SimulateGravity);
	ImGui::DragFloat("GravityX", &PhysicsEntity::m_Gravity.x, 1.f);
	ImGui::DragFloat("GravityY", &PhysicsEntity::m_Gravity.y, 1.f);
	ImGui::DragFloat("GravityZ", &PhysicsEntity::m_Gravity.z, 1.f);
	ImGui::Separator();
	ImGui::Checkbox("Simulate Drag: ", &PhysicsEntity::m_SimulateDrag);
	ImGui::DragFloat("Drag", &PhysicsEntity::m_Drag); // float
	ImGui::DragFloat("Drag Coef", &PhysicsEntity::m_DragCoef); // float
	ImGui::Separator();
	ImGui::Checkbox("Simulate Lift: ", &PhysicsEntity::m_SimulateLift);
	ImGui::DragFloat("Lift", &PhysicsEntity::m_Lift);
	ImGui::DragFloat("Lift Coef", &PhysicsEntity::m_LiftCoef);
	ImGui::Separator();
	ImGui::Checkbox("Simulate Friction: ", &PhysicsEntity::m_SimulateFriction);
	ImGui::DragFloat("Friction: ", &PhysicsEntity::m_Friction);
	ImGui::DragFloat("Friction Coef: ", &PhysicsEntity::m_FrictionCoef);

	ImGui::Spacing();
	ImGui::SeparatorText("External Forces Attributes");
	ImGui::Spacing();
	ImGui::Checkbox("Simulate Wind: ", &PhysicsEntity::m_SimulateWind); // vector 3
	ImGui::DragFloat("Wind X: ", &PhysicsEntity::m_Wind.x);
	ImGui::DragFloat("Wind Y: ", &PhysicsEntity::m_Wind.y);
	ImGui::DragFloat("Wind Z: ", &PhysicsEntity::m_Wind.z);

	ImGui::End();

	#pragma region Analysis Window

	ImGui::Begin("Analysis");
	ImGui::SeparatorText("General Statistics");
	ImGui::Text("Mouse X: %.0f", WindowManager::m_MouseX); ImGui::SameLine(); ImGui::Text("Mouse Y: %.0f", WindowManager::m_MouseY);
	ImGui::Text("Mouse NDC X: %.1f", WindowManager::m_MouseNDCX); ImGui::SameLine(); ImGui::Text("Mouse NDC Y: %.1f", WindowManager::m_MouseNDCY);

	ImGui::Separator();
	ImGui::Text("Frame Counter: %.1f", m_SimpleCount);
	ImGui::Text("(Unscaled) Frame Time: %.2f", 100 * ((m_Timer->GetDeltaTime() * 60.f) * 60.f));
	ImGui::Text("(Scaled) Frame Time: %.2f",  (FPS60 * 60.f) * 60.f);
	ImGui::Text("Simulation Time(CPU/ms): %.2f", m_SimulationTime);
	ImGui::Text("Simulation Latency(GPU):");

	ImGui::Spacing();
	ImGui::SeparatorText("Object Statistics");
	ImGui::Text("Object Count: %d", m_CurrentScreen->GetObjects().size() - 4);
	ImGui::Text("Rigidbody Count: %d", Rigidbody3DObject::m_RigidbodyCount);
	ImGui::Text("Particle Count: %d", MassAggregate::m_PointCount);
	ImGui::Text("Spring Count: %d", MassAggregate::m_SpringCount);

	ImGui::Spacing();
	ImGui::SeparatorText("Spatilisation Statistics");

	bool t_tempChecking = false;
	ImGui::Checkbox("Activate Octree", &t_tempChecking);
	ImGui::Text("Octants: %d", 0);
	ImGui::Text("Algo Comp Time: ");

	ImGui::Separator();

	ImGui::Checkbox("Activate BSP", &t_tempChecking);
	ImGui::Text("BSP Divisions: %d", 0);
	ImGui::Text("Algo Comp Time: ");

	ImGui::Separator();

	ImGui::Checkbox("Activate Spatial Hashing", &t_tempChecking);
	ImGui::Text("Spatial Hashing Cells: %d", 0);
	ImGui::Text("Algo Comp Time: ");

	ImGui::End();

	#pragma endregion

	GuizmoRendering();
}

void ScreenManager::TransitionScreen(SCREENS screen, ID3D11Device* device)
{
	m_CurrentScreen = nullptr; 
	m_CollisionSolutionMap.clear(); 
	
	switch (screen)
	{
		case SCREENS::SCREEN_BASIC: m_CurrentScreen = new BasicScreen("Basic Screen", device); m_ScreenState = SCREENS::SCREEN_BASIC; break;
		case SCREENS::SCREEN_EPA: m_CurrentScreen = new EPAScreen("EPA Screen", device); m_ScreenState = SCREENS::SCREEN_EPA; break;
		case SCREENS::SCREEN_GJK: m_CurrentScreen = new GJKScreen("GJK Screen", device); m_ScreenState = SCREENS::SCREEN_GJK; break;
		case SCREENS::SCREEN_MASS_AGG: m_CurrentScreen = new MassAggScreen("MassAgg Screen", device); m_ScreenState = SCREENS::SCREEN_MASS_AGG; break;
		case SCREENS::SCREEN_SAT: m_CurrentScreen = new SATScreen("SAT Screen", device); m_ScreenState = SCREENS::SCREEN_SAT; break;
	}
}

void ScreenManager::PickingTest()
{
	if (m_CurrentScreen == nullptr) { return; }

	XMMATRIX view, proj;
	view = m_Camera->GetViewMatrix();
	proj = m_Camera->GetProjectionMatrix();
	
	XMVECTOR roScreen, rdScreen;
	roScreen = XMVectorSet(WindowManager::m_MouseX, WindowManager::m_MouseY, 0.0f, 1.0f);
	rdScreen = XMVectorSet(WindowManager::m_MouseX, WindowManager::m_MouseY, 1.0f, 1.0f);

	XMVECTOR ro, rd;
	ro = XMVector3Unproject(roScreen, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, proj, view, XMMatrixIdentity());
	rd = XMVector3Unproject(rdScreen, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, proj, view, XMMatrixIdentity());
	rd = XMVector3Normalize(rd - ro);

	// NOTE: Ray Start
	XMFLOAT3 t_rayStartFloat;
	XMStoreFloat3(&t_rayStartFloat, ro);
	
	// NOTE: Ray Direction
	XMFLOAT3 t_rayDirectionFloat;
	XMStoreFloat3(&t_rayDirectionFloat, rd);

	// NOTE: Ray Object
	GameObjectEntity* t_RayObject = new GameObjectEntity();
	t_RayObject->AddComponent<RayCollider>()->Construct(t_rayStartFloat, t_rayDirectionFloat);
	CollisionManager t_tempManager;
	CollisionManifold t_tempManifold;

	if (!m_CurrentScreen->GetObjects().empty())
	{
		for (int i = 0; i < m_CurrentScreen->GetObjects().size(); ++i)
		{
			t_tempManifold = t_tempManager.CheckCollisions(t_RayObject, m_CurrentScreen->GetObjects()[i], m_CollisionSolutionMap);
			if (t_tempManifold.hasCollision)
			{
				m_GuizmoObject = t_tempManifold.hitObject;
				break;
			}
			m_CollisionSolutionMap.clear();
		}
	}

	delete t_RayObject;
}
