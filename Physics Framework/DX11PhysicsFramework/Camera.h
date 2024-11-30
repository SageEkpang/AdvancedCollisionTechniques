#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Structures.h"
#include "Constants.h"

using namespace DirectX;

class Camera
{
private:

	XMFLOAT3 m_Eye; 
	XMFLOAT3 m_At;
	XMFLOAT3 m_Up;

	FLOAT _windowWidth;
	FLOAT _windowHeight;

	FLOAT _nearDepth;
	FLOAT _farDepth;

	// CAMERA VARIABLE(s)
	float m_CameraSpeed;
	float m_CameraRotationSpeed;

	XMFLOAT3 m_ForwardLook;

	XMFLOAT4X4* m_World;
	XMFLOAT4X4 m_ViewMatrix;
	XMFLOAT4X4 m_ProjectionMatrix;

public:

	// CLASS FUNCTION(s)
	Camera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth);
	~Camera();

	// BASE FUNCTION(s)
	void Update(const float deltaTime);

	// GETTER FUNCTION(s)
	inline XMFLOAT4X4 GetView() const { return m_ViewMatrix; }
	inline XMFLOAT4X4 GetProjection() const { return m_ProjectionMatrix; }

	inline XMFLOAT4X4 GetViewProjection() const;

	inline XMFLOAT3 GetPosition() const { return m_Eye; }
	inline XMFLOAT3 GetLookAt() const { return m_At; }
	inline XMFLOAT3 GetUp() const { return m_Up; }

	XMMATRIX& GetCameraMatrix();

	// SETTER FUNCTION(s)
	inline void SetPosition(XMFLOAT3 position) { m_Eye = position; }
	inline void SetLookAt(XMFLOAT3 lookAt) { m_At = lookAt; }
	inline void SetUp(XMFLOAT3 up) { m_Up = up; }

	void SetCameraPosition(float x, float y, float z);

	// HELPER FUNCTION(s)
	void Reshape(FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth);
};

#endif
