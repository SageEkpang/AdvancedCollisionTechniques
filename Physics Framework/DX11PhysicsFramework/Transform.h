#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H


// NEEDED INCLUDE(s)
#include "Structures.h"
#include "Quaternion.h"
#include "Vector.h"

class Transform
{
private:

	// BASE VARIABLE(s)
	Vector3 m_Position;
	Vector3 m_Origin;
	Vector3 m_Scale;
	Quaternion4 m_Orientation;

	// WORLD VARIABLE(s)
	Transform* m_Parent = nullptr;
	XMFLOAT4X4* m_World;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	Transform();

	/// <summary> Default Deconstructor for Clas </summary>
	~Transform();



	// BASE FUNCTION(s)

	/// <summary> Default Base Update Class for Class </summary>
	void Update(float DeltaTime);



	// ADDITIONAL FUNCTION(s)

	/// <summary> Function to Move Entity (Vector3) </summary>
	void Move(Vector3 Direction);

	/// <summary> Function to Resize Entity (Scale3) </summary>
	void Resize(Vector3 Direction);


	// GETTER FUNCTION(s)

	inline Transform* GetParent() { return m_Parent; }

	/// <summary> Getter function for Transform Position </summary>
	inline Vector3 GetPosition() { return m_Position; }

	/// <summary> Getter function for Transform Origin </summary>
	inline Vector3 GetOrigin() { return m_Origin; }

	/// <summary> Getter function for Transform Scale </summary>
	inline Vector3 GetScale() { return m_Scale; }

	/// <summary> Getter function for Transform Rotation (Derived from Quaternion) </summary>
	Vector3 GetRotation() const { return Quaternion::MakeEulerAnglesFromQ(m_Orientation); }

	/// <summary> Getter function for Transform Orientation </summary>
	Quaternion4 GetOrientation() const { return m_Orientation; }

	/// <summary> Getter function for World Matrix </summary>
	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(m_World); }



	// SETTER FUNCTION(s)
	void SetParent(Transform* Parent) { m_Parent = Parent; }

	// position
	void SetPosition(Vector3 Position) { m_Position = Position; }
	void SetPosition(float x, float y, float z) { m_Position = Vector3(x, y, z); }

	void SetOrigin(Vector3 origin) { m_Origin = origin; }

	// scale
	void SetScale(Vector3 Scale) { m_Scale = Scale; }
	void SetScale(float x, float y, float z) { m_Scale = Vector3(x, y, z); }

	// rotation
	void SetRotation(Vector3 rotation) { m_Orientation = Quaternion::MakeQFromEulerAngles(rotation.x, rotation.y, rotation.z); } // Quaternion Rotation
	void SetRotation(float x, float y, float z) { m_Orientation = Quaternion::MakeQFromEulerAngles(x, y, z); } // Quaternion Rotation
	void SetOrientation(Quaternion4 orientation) { m_Orientation = orientation; } // Quaternion Rotation
};

#endif