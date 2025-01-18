#include "SATCollider.h"
#include "BoxCollider.h"


SATCollider::~SATCollider()
{



}

bool SATCollider::OverlapAxis(BoxCollider* box, Vector3* axis)
{
	Interval t_ShapeA = Vector::GetInterval(box, axis);
	Interval t_ShapeB = Vector::GetInterval(box, axis);

	return (t_ShapeB.min <= t_ShapeA.max) && (t_ShapeA.min <= t_ShapeB.max);
}
