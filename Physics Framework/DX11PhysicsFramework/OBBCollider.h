#ifndef OBB_COLLIDER_H
#define OBB_COLLIDER_H

// ABSTRACT CLASS(s)
#include "ColliderEntity.h"

class OBBCollider : public ColliderEntity
{
private:

	Vector3 m_Max;
	Vector3 m_Min;
	Vector3 m_Orientation;

	Vector3 m_CenterPoint; // Position
	Vector3 m_U[3]; // Tensor // NOTE: Local X, Y, Z AXES
	float m_Extents[3]; // Extents

	float m_Size[3] = { 0 }; // TODO: Fill this with values // TODORE: Depricated, remove these when possible
	float m_OrientationArray[9] = { 0 }; // Make a function for this instead // TODORE: Depricated, remove these when possible

public:

	// CLASS FUNCTION(s)
	//OBBCollider(Transform* transform, Vector3 rotation)
	//{ 


	//}

	// GETTER FUNCTION(s)
	Vector3 GetOrientation() { return m_Orientation; }
	const float* GetOrientationArray() { return m_OrientationArray; }

	Vector3* GetUArray() { return m_U; }


	// HELPER FUNCTION(s)
	Vector3 NearestPoint(Vector3 point);
	bool PointInOBB(Vector3 point);
};

#endif