#ifndef TRANSFORM_H
#define TRANSFORM_H

// NEEDED INCLUDE(s)
#include "Quaternion.h"
#include "Vector3.h"
#include <directxmath.h>

using namespace DirectX;

class Transform
{
public:

	// BASE VARIABLE(s)
	Vector3 m_Position;
	Vector3 m_Scale;
	Quaternion4 m_Orientation;

	// WORLD VARIABLE(s)
	Transform* m_Parent = nullptr;
	DirectX::XMFLOAT4X4* m_World;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	Transform();

	/// <summary> Default Deconstructor for Clas </summary>
	~Transform();


	// BASE FUNCTION(s)

	/// <summary> Default Base Update Class for Class </summary>
	void Update(float DeltaTime);


	// GETTER FUNCTION(s)

	inline Transform* GetParent() { return m_Parent; }

	/// <summary> Getter function for Transform Rotation (Derived from Quaternion) </summary>
	Vector3 GetRotation() { return Quaternion::MakeEulerAnglesFromQ(m_Orientation); }

	/// <summary> Getter function for World Matrix </summary>
	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(m_World); }


	// SETTER FUNCTION(s)
	void SetParent(Transform* Parent) { m_Parent = Parent; }

	// rotation
	void SetRotation(Vector3 rotation) { m_Orientation = Quaternion::MakeQFromEulerAngles(rotation.x, rotation.y, rotation.z); } // Quaternion Rotation
	void SetRotation(float x, float y, float z) { m_Orientation = Quaternion::MakeQFromEulerAngles(x, y, z); } // Quaternion Rotation
	void SetOrientation(Quaternion4 orientation) { m_Orientation = orientation; } // Quaternion Rotation
};

#endif