#pragma once
#ifndef SAT_COLLIDER_H
#define SAT_COLLIDER_H

// ABSTRACT CLASS(s)
#include "Collider.h"

#include "Constants.h"
#include "Structures.h"

class SATCollider : public Collider
{
private:

	Interval m_SATInterval;

public:

	// CLASS FUNCTION(s)
	SATCollider(Transform* transform, Interval interval) : Collider(transform) {m_SATInterval = interval; }
	~SATCollider();


	// HELPER FUNCTION(s)
	// NOTE: May need to change the box to just a transform or collider variable
	bool OverlapAxis(BoxCollider* box, Vector3* axis);




	// GETTER FUNCTION(s)
	Interval GetInterval() const { return m_SATInterval; }




	// SETTER FUNCTION(s)
	void SetInterval(Interval interval) { m_SATInterval = interval; }

};

#endif
