#pragma once
#ifndef SAT_COLLIDER_H
#define SAT_COLLIDER_H

// ABSTRACT CLASS(s)
#include "Collider.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

class SATCollider : public Collider
{
private:

	Interval m_SATInterval;

	Vector3 m_centrePoint; // Position
	Vector3 m_U[3]; // Local x-, y-, and z-
	Vector3 t_Extents; // Halfwidth Extents of OBB along Each Axis

public:

	// CLASS FUNCTION(s)
	SATCollider(Transform* transform, Interval interval) : Collider(transform) {m_SATInterval = interval; }
	~SATCollider();


	// HELPER FUNCTION(s)
	bool OverlapAxis(BoxCollider* box, Vector3* axis);


	// GETTER FUNCTION(s)
	Interval GetInterval() const { return m_SATInterval; }



	// SETTER FUNCTION(s)
	void SetInterval(Interval interval) { m_SATInterval = interval; }

};

#endif
