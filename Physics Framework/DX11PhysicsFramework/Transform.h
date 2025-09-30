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
	float m_Matrix[16];

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	Transform()
	{
		m_Position = Vector3(0, 0, 0);
		m_Scale = Vector3(1, 1, 1);
		m_Orientation = Quaternion4(0, 0, 0, 1);

		m_Matrix[0] = 1.f, m_Matrix[1] = 0.f, m_Matrix[2] = 0.f, m_Matrix[3] = 0.f;
		m_Matrix[4] = 0.f, m_Matrix[5] = 1.f, m_Matrix[6] = 0.f, m_Matrix[7] = 0.f;
		m_Matrix[8] = 0.f, m_Matrix[9] = 0.f, m_Matrix[10] = 1.f, m_Matrix[11] = 0.f;
		m_Matrix[12] = 0.f, m_Matrix[13] = 0.f, m_Matrix[14] = 0.f, m_Matrix[15] = 1.f;

	}

	Transform(Vector3 position, Vector3 scale, Quaternion4 orientation)
	{
		this->m_Position = position;
		this->m_Scale = scale;
		this->m_Orientation = orientation;

		m_Matrix[0] = 1.f, m_Matrix[1] = 0.f, m_Matrix[2] = 0.f, m_Matrix[3] = position.x;
		m_Matrix[4] = 0.f, m_Matrix[5] = 1.f, m_Matrix[6] = 0.f, m_Matrix[7] = position.y;
		m_Matrix[8] = 0.f, m_Matrix[9] = 0.f, m_Matrix[10] = 1.f, m_Matrix[11] = position.z;
		m_Matrix[12] = 0.f, m_Matrix[13] = 0.f, m_Matrix[14] = 0.f, m_Matrix[15] = 1.f;

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