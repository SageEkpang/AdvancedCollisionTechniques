#include "Camera.h"
#include "WindowManager.h"

Camera::Camera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth)
	: m_Eye(position), m_At(at), m_Up(up), _windowWidth(windowWidth), _windowHeight(windowHeight), _nearDepth(nearDepth), _farDepth(farDepth)
{
	m_World = new XMFLOAT4X4();

	m_CameraSpeed = 15.0f;
	m_CameraRotationSpeed = 10.f;

	m_ForwardLook = XMFLOAT3(0.0f, 0.0f, 1.0f);

	// Set View Matrix
	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixLookToLH(XMLoadFloat3(&m_Eye), XMLoadFloat3(&m_ForwardLook), XMLoadFloat3(&m_Up)));

	// Set Projection Matrix
	XMMATRIX TempMat;
	float t_Aspect = _windowWidth / _windowHeight;
	TempMat = XMMatrixPerspectiveFovLH(XMConvertToRadians(90), t_Aspect, 1.0f, 100.0f);
	XMStoreFloat4x4(&m_ProjectionMatrix, TempMat);
}

Camera::~Camera()
{
	if (m_World != nullptr)
	{
		delete m_World;
		m_World = nullptr;
	}
}

void Camera::Update(const float deltaTime)
{
	// Getting the Inverse View Matrix
	XMMATRIX t_TempWorld = XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_ViewMatrix));

	// MOVEMENT // TODO: Could add a smoothing function to the camera to move better
	if (GetAsyncKeyState('W')) { t_TempWorld.r[3] += t_TempWorld.r[2] * m_CameraSpeed * deltaTime; } // Move Forward
	if (GetAsyncKeyState('A')) { t_TempWorld.r[3] -= t_TempWorld.r[0] * m_CameraSpeed * deltaTime; } // Move Left
	if (GetAsyncKeyState('S')) { t_TempWorld.r[3] -= t_TempWorld.r[2] * m_CameraSpeed * deltaTime; } // Move Back
	if (GetAsyncKeyState('D')) { t_TempWorld.r[3] += t_TempWorld.r[0] * m_CameraSpeed * deltaTime; } // Move Right

	// UP AND DOWN
	if (GetAsyncKeyState('E')) { t_TempWorld.r[3] += t_TempWorld.r[1] * m_CameraSpeed * deltaTime; } // Move Up
	if (GetAsyncKeyState('Q')) { t_TempWorld.r[3] -= t_TempWorld.r[1] * m_CameraSpeed * deltaTime; } // Move Down


	if (WindowManager::m_CtrlDown == true && WindowManager::m_MouseWheel > 0)
	{
		m_CameraSpeed += 1;
		m_CameraSpeed = std::clamp(m_CameraSpeed, 0.1f, 10.f);
	}
	else if (WindowManager::m_CtrlDown == true && WindowManager::m_MouseWheel < 0)
	{
		m_CameraSpeed -= 1;
		m_CameraSpeed = std::clamp(m_CameraSpeed, 0.1f, 10.f);
	}
	else if (WindowManager::m_CtrlDown == false && WindowManager::m_MouseWheel != 0)
	{
		WindowManager::m_MouseWheel = 0;
	}

	if (WindowManager::m_MouseButtonRightDown == true)
	{
		if (m_SavedPosSet == false)
		{
			m_SavedPositionX = WindowManager::m_MouseNDCX;
			m_SavedPositionY = WindowManager::m_MouseNDCY;
			m_SavedPosSet = true;
		}

		XMMATRIX CamRotationX = XMMatrixRotationAxis(t_TempWorld.r[1], XMConvertToRadians(
			(WindowManager::m_MouseNDCX - m_SavedPositionX) * (m_CameraRotationSpeed * 100) * deltaTime)
		);

		t_TempWorld.r[0] = XMVector3TransformNormal(t_TempWorld.r[0], CamRotationX);
		t_TempWorld.r[2] = XMVector3TransformNormal(t_TempWorld.r[2], CamRotationX);

		//XMMATRIX CamRotationY = XMMatrixRotationAxis(t_TempWorld.r[0], XMConvertToRadians(
		//	(-WindowManager::m_MouseNDCY - m_SavedPositionY) * (m_CameraRotationSpeed * 20) * deltaTime)
		//);

		//t_TempWorld.r[1] = XMVector3TransformNormal(t_TempWorld.r[1], CamRotationY);
		//t_TempWorld.r[2] = XMVector3TransformNormal(t_TempWorld.r[2], CamRotationY);

		//XMMATRIX CamRotationZ_X = XMMatrixRotationAxis(
		//	t_TempWorld.r[2], XMConvertToRadians((WindowManager::m_MouseNDCX - m_SavedPositionX) / 360.f)
		//);

		//XMMATRIX CamRotationZ_Y = XMMatrixRotationAxis(
		//	t_TempWorld.r[2], XMConvertToRadians((-WindowManager::m_MouseNDCY - m_SavedPositionY) / 360.f)
		//);

		//t_TempWorld.r[0] = XMVector3TransformNormal(t_TempWorld.r[0], CamRotationZ_Y);
		//t_TempWorld.r[1] = XMVector3TransformNormal(t_TempWorld.r[1], CamRotationZ_X);
	}
	else
	{
		m_SavedPositionX = 0;
		m_SavedPositionY = 0;
		m_SavedPosSet = false;
	}

	XMStoreFloat4x4(m_World, t_TempWorld);
	XMMATRIX t_TempView = XMMatrixInverse(nullptr, XMLoadFloat4x4(m_World));
	XMStoreFloat4x4(&m_ViewMatrix, t_TempView);
}

inline void Camera::SetCameraPosition(float x, float y, float z)
{
	XMMATRIX TempWorld = XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_ViewMatrix));

	TempWorld.r[3] += TempWorld.r[0] * x;
	TempWorld.r[3] += TempWorld.r[1] * y;
	TempWorld.r[3] += TempWorld.r[2] * z;

	XMStoreFloat4x4(m_World, TempWorld);
	XMMATRIX TempView = XMMatrixInverse(nullptr, XMLoadFloat4x4(m_World));
	XMStoreFloat4x4(&m_ViewMatrix, TempView);

	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixLookAtLH(XMLoadFloat3(&m_Eye), XMLoadFloat3(&m_At), XMLoadFloat3(&m_Up))); // Set AT needs this for the view matrix
}

void Camera::Reshape(FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth)
{
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	_nearDepth = nearDepth;
	_farDepth = farDepth;
}

XMFLOAT4X4 Camera::GetViewProjection() const 
{ 
	XMMATRIX view = XMLoadFloat4x4(&m_ViewMatrix);
	XMMATRIX projection = XMLoadFloat4x4(&m_ProjectionMatrix);

	XMFLOAT4X4 viewProj;

	XMStoreFloat4x4(&viewProj, view * projection);

	return viewProj;
}

XMMATRIX& Camera::GetCameraMatrix()
{
	XMMATRIX t_TempMat = XMLoadFloat4x4(m_World);
	return t_TempMat;
}
