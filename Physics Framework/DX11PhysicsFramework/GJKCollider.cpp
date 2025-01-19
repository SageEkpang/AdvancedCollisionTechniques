#include "GJKCollider.h"

GJKCollider::GJKCollider()
{






}

GJKCollider::~GJKCollider()
{





}

bool GJKCollider::GJKCollision(Collider* colliderA, Collider* colliderB)
{
	// TODO: Find what unit_x is
	Vector3 t_UnitX = Vector3(1, 0, 0);
	Vector3 t_Support = Support(colliderA, colliderB, t_UnitX);

	// Simplex is an array of points, max count is 4
	Simplex t_Points;
	t_Points.push_front(t_Support);

	Vector3 t_Direction = t_Support * -1;

	// New Direction
	while (true)
	{
		t_Support = Support(colliderA, colliderB, t_Direction);
		
		if (Vector::CalculateDotProduct(t_Support, t_Direction) <= 0)
		{
			return false; // No Collision
		}

		t_Points.push_front(t_Support);

		//if (NextSimplex(t_Points, t_Direction))
		//{
		//	return true;
		//}

	}



	return false;
}

bool GJKCollider::NextSimplex(Simplex& points, Vector3& direction)
{
	switch (points.GetSize())
	{
		case 2: Line(points, direction);
		case 3: Triangle(points, direction);
		case 4: Tetrahedron(points, direction);
	}

	return false;
}

bool GJKCollider::Line(Simplex points, Vector3 direction)
{
	Vector3 t_A = points[0];
	Vector3 t_B = points[1];

	Vector3 t_AB = t_B - t_A;
	Vector3 t_AO = - t_A;

	if (SameDirection(t_AB, t_AO))
	{
		direction = Vector::CalculateCrossProductV(Vector::CalculateCrossProductV(t_AB, t_AO), t_AB);
	}
	else
	{
		points = { t_A };
		direction = t_AO;
	}

	return false;
}

bool GJKCollider::Triangle(Simplex points, Vector3 direction)
{
	Vector3 t_A = points[0];
	Vector3 t_B = points[1];
	Vector3 t_C = points[2];

	Vector3 t_AB = t_B - t_A;
	Vector3 t_AC = t_C - t_A;
	Vector3 t_AO = - t_A;

	Vector3 t_ABC = Vector::CalculateCrossProductV(t_AB, t_AC);

	if (SameDirection(Vector::CalculateCrossProductV(t_ABC, t_AC), t_AO))
	{
		if (SameDirection(t_AC, t_AO))
		{
			points = { t_A, t_C };
			direction = Vector::CalculateCrossProductV(Vector::CalculateCrossProductV(t_AC, t_AO), t_AC);
		}
		else
		{
			return Line(points = { t_A, t_B}, direction);
		}
	}
	else
	{

	}



	return false;
}

bool GJKCollider::Tetrahedron(Simplex points, Vector3 direction)
{


	return false;
}

bool GJKCollider::SameDirection(Vector3 direction, Vector3 Ao)
{
	return Vector::CalculateDotProduct(direction, Ao) > 0;
}

Vector3 GJKCollider::Support(Collider* colliderA, Collider* colliderB, Vector3 direction)
{
	// REWORK: Rework the collider class so it knows what vertices it has, this is used for this function
	Vector3 t_TempA = colliderA->FindFurthestPoint(direction);
	Vector3 t_TempB = colliderB->FindFurthestPoint(-direction); // TODO: Need to actually check if it is working

	return t_TempA - t_TempB;
}
