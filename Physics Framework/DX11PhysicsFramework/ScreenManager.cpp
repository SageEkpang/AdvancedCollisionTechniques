#include "ScreenManager.h"

ScreenManager::ScreenManager(ID3D11Device* device)
{
	// Assign Basic Screen to Screen Variable
	m_CurrentScreen = new BasicScreen("BasicScreen", device);

	// Setup Camera
	XMFLOAT3 eye = XMFLOAT3(0.0f, 5.0f, 0.0f);
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

	for (auto& v : m_CurrentScreen->GetObjects())
	{
		float ObjectTranslation[3] , ObjectRotation[3], ObjectScale[3];

		ObjectTranslation[0] = v->m_Transform.m_Position.x;
		ObjectTranslation[1] = v->m_Transform.m_Position.y;
		ObjectTranslation[2] = v->m_Transform.m_Position.z;

		ObjectRotation[0] = v->m_Transform.GetRotation().x;
		ObjectRotation[1] = v->m_Transform.GetRotation().y;
		ObjectRotation[2] = v->m_Transform.GetRotation().z;

		ObjectScale[0] = v->m_Transform.m_Scale.width;
		ObjectScale[1] = v->m_Transform.m_Scale.height;
		ObjectScale[2] = v->m_Transform.m_Scale.length;

		ImGuizmo::RecomposeMatrixFromComponents(ObjectTranslation, ObjectRotation, ObjectScale, v->m_Transform.m_Matrix);
		float matrixTranslation[3], matrixRotation[3], matrixScale[3];
		ImGuizmo::DecomposeMatrixToComponents(v->m_Transform.m_Matrix, matrixTranslation, matrixRotation, matrixScale);

		ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, v->m_Transform.m_Matrix);

		float ViewMatrix[16] = 
		{
			m_Camera->GetView()._11, m_Camera->GetView()._12, m_Camera->GetView()._13, m_Camera->GetView()._14,
			m_Camera->GetView()._21, m_Camera->GetView()._22, m_Camera->GetView()._23, m_Camera->GetView()._24,
			m_Camera->GetView()._31, m_Camera->GetView()._32, m_Camera->GetView()._33, m_Camera->GetView()._34,
			m_Camera->GetView()._41, m_Camera->GetView()._42, m_Camera->GetView()._43, m_Camera->GetView()._44,
		};

		float ProjectionMatrix[16] =
		{
			m_Camera->GetProjection()._11, m_Camera->GetProjection()._12, m_Camera->GetProjection()._13, m_Camera->GetProjection()._14,
			m_Camera->GetProjection()._21, m_Camera->GetProjection()._22, m_Camera->GetProjection()._23, m_Camera->GetProjection()._24,
			m_Camera->GetProjection()._31, m_Camera->GetProjection()._32, m_Camera->GetProjection()._33, m_Camera->GetProjection()._34,
			m_Camera->GetProjection()._41, m_Camera->GetProjection()._42, m_Camera->GetProjection()._43, m_Camera->GetProjection()._44,
		};

		ImGuiIO& io = ImGui::GetIO();
		ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
		ImGuizmo::Manipulate(ViewMatrix, ProjectionMatrix, mCurrentGizmoOperation, mCurrentGizmoMode, v->m_Transform.m_Matrix, NULL);
	}

	ImGui::End();

}

void ScreenManager::GUIShowcase(ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	#pragma region Screen Select

	ImGui::Begin("Scenes");
	if (ImGui::Button("Basic Scene", ImVec2(ImGui::GetWindowWidth() - 15, 30))) { delete m_CurrentScreen; m_CurrentScreen = nullptr; m_CurrentScreen = new BasicScreen("Basic Screen", device); }
	if (ImGui::Button("EPA Scene", ImVec2(ImGui::GetWindowWidth() - 15, 30))) { delete m_CurrentScreen; m_CurrentScreen = nullptr; m_CurrentScreen = new EPAScreen("EPA Screen", device); }
	if (ImGui::Button("GJK Scene", ImVec2(ImGui::GetWindowWidth() - 15, 30))) { delete m_CurrentScreen; m_CurrentScreen = nullptr; m_CurrentScreen = new GJKScreen("GJK Screen", device); }
	if (ImGui::Button("MassAgg Scene", ImVec2(ImGui::GetWindowWidth() - 15, 30))) { delete m_CurrentScreen; m_CurrentScreen = nullptr; m_CurrentScreen = new MassAggScreen("MassAggregate Screen", device); }
	if (ImGui::Button("SAT Scene", ImVec2(ImGui::GetWindowWidth() - 15, 30))) { delete m_CurrentScreen; m_CurrentScreen = nullptr; m_CurrentScreen = new SATScreen("SAT Screen", device); }
	ImGui::End();

	#pragma endregion
	 
	ImGui::Begin("General Window");
	
	ImGui::SeparatorText("Scene Attributes");
	ImGui::Spacing();

	if (ImGui::Button("Reset Scene", ImVec2(ImGui::GetWindowWidth() - 15, 30))) {}

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
	ImGui::Text("Frame Counter: %.1f", m_SimpleCount);
	ImGui::Text("(Unscaled) Frame Time: %.2f", 100 * ((m_Timer->GetDeltaTime() * 60.f) * 60.f));
	ImGui::Text("(Scaled) Frame Time: %.2f",  (FPS60 * 60.f) * 60.f);
	ImGui::Text("Simulation Time(CPU/ms): %.2f", m_SimulationTime);
	ImGui::Text("Simulation Latency(GPU):");

	ImGui::Spacing();
	ImGui::SeparatorText("Object Statistics");
	ImGui::Text("Object Count: %d", m_CurrentScreen->GetObjects().size() - 1);
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

void ScreenManager::PickingTest(int mouseX, int mouseY)
{
	XMMATRIX world, view, proj;
	
	world = XMLoadFloat4x4(m_CurrentScreen->GetObjects()[1]->GetWorld());
	view = m_Camera->GetViewMatrix();
	proj = m_Camera->GetProjectionMatrix();

	DirectX::XMVECTOR roScreen, rdScreen;
	XMVECTOR ro, rd;
	roScreen = XMVectorSet(mouseX, mouseY, 0.1, 1.0f);
	rdScreen = XMVectorSet(mouseX, mouseY, 1, 1.0f);

	ro = XMVector3Unproject(roScreen, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, proj, view, world);
	rd = XMVector3Unproject(rdScreen, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, proj, view, world);
	rd = XMVector3Normalize(rd - ro);



}
