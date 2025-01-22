#include "Plane.h"

bool Plane::isPointOnPositiveSide(const Vector3& Q) const
{
	float d = Vector::CalculateDotProduct(n, Q) + this->d;
	if (d >= 0) return true;
	return false;
}
