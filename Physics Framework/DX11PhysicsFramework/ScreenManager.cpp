#include "ScreenManager.h"

ScreenManager::ScreenManager(ID3D11Device* device)
{
	// Assign Basic Screen to Screen Variable
	m_CurrentScreen = new BasicScreen("BasicScreen", device);

	// Setup Camera
	XMFLOAT3 eye = XMFLOAT3(0.0f, 5.0f, 0.0f);
	XMFLOAT3 at = XMFLOAT3(0.0f, 2.0f, 0.0f);
	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);

	_camera = new Camera(eye, at, up, WINDOW_WIDTH, WINDOW_HEIGHT, 0.01f, 200.0f);

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

void ScreenManager::Showcase(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	// Transpose Matrices and Load Information from Calculated Update function
	constantBufferData.View = XMMatrixTranspose(_camera->GetViewMatrix());
	constantBufferData.Projection = XMMatrixTranspose(_camera->GetProjectionMatrix());
	constantBufferData.EyePosW = _camera->GetPosition();
	constantBufferData.light = basicLight;

	// Draw the Current Physics Screen
	m_CurrentScreen->Draw(constantBufferData, constBuff, pImmediateContext, device);
}

void ScreenManager::GUIShowcase()
{

	ImGui::Begin("Scenes");
	if (ImGui::Button("Basic Scene", ImVec2(ImGui::GetWindowWidth() - 15, 30))) { }
	if (ImGui::Button("EPA Scene", ImVec2(ImGui::GetWindowWidth() - 15, 30))) { }
	if (ImGui::Button("GJK Scene", ImVec2(ImGui::GetWindowWidth() - 15, 30))) { }
	if (ImGui::Button("MassAgg Scene", ImVec2(ImGui::GetWindowWidth() - 15, 30))) { }
	if (ImGui::Button("SAT Scene", ImVec2(ImGui::GetWindowWidth() - 15, 30))) { }
	ImGui::End();


	ImGui::Begin("General Window");
	
	bool s = false;
	ImGui::Checkbox("Wireframe", &s);
	ImGui::Checkbox("Points", &s);
	ImGui::Checkbox("Fluid", &s);
	ImGui::Checkbox("Mesh", &s);
	ImGui::Checkbox("Basis", &s);
	ImGui::Checkbox("Springs", &s);
	ImGui::Checkbox("Contacts", &s);
	ImGui::End();



	ImGui::Begin("Analysis");
	ImGui::Text("Frame Counter: %f", m_SimpleCount);
	ImGui::Text("Frame Time: %f", m_Timer->GetDeltaTime() * 1000000);
	ImGui::Text("Simulation Time(CPU):");
	ImGui::Text("Simulation Latency(GPU):");

	ImGui::Separator();

	ImGui::Text("Particle Count");
	ImGui::Text("Diffuse Count");
	ImGui::Text("Rigidbody Count");
	ImGui::Text("SpringCount Count");

	ImGui::Separator();
	ImGui::End();




}
