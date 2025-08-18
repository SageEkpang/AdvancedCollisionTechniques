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

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	Transform()
	{
		m_Position = Vector3(0, 0, 0);
		m_Scale = Vector3(1, 1, 1);
		m_Orientation = Quaternion4(0, 0, 0, 1);
	}

	/// <summary> Default Deconstructor for Clas </summary>
	~Transform()
	{

	}


	// BASE FUNCTION(s)

	/// <summary> Default Base Update Class for Class </summary>
	void Update(float DeltaTime);


	// GETTER FUNCTION(s)

	/// <summary> Getter function for Transform Rotation (Derived from Quaternion) </summary>
	Vector3 GetRotation() { return Quaternion4::MakeEulerAnglesFromQ(m_Orientation); }

	/// <summary> Getter function for World Matrix </summary>

	// rotation
	void SetRotation(Vector3 rotation) { m_Orientation = Quaternion4::MakeQFromEulerAngles(rotation.x, rotation.y, rotation.z); } // Quaternion Rotation
	void SetRotation(float x, float y, float z) { m_Orientation = Quaternion4::MakeQFromEulerAngles(x, y, z); } // Quaternion Rotation
	void SetOrientation(Quaternion4 orientation) { m_Orientation = orientation; } // Quaternion Rotation
};

#endif