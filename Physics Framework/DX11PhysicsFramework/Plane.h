#pragma once
#ifndef PLANE_H
#define PLANE_H

#include "Constants.h"
#include "Structures.h"
#include "Vector.h"

class Plane
{
public:

	Vector3 n; // Normal
	float d; // Signed Distance
	float sqrtNLength; // Normal Length Squared

	Plane() = default;

	Plane(const Vector3& N, const Vector3& P)
		: n(N), d(-Vector::CalculateDotProduct(N, P)), sqrtNLength(Vector::Magnitude(N))
	{
		
	}

	bool isPointOnPositiveSide(const Vector3& Q) const;
};

#endif // Plane