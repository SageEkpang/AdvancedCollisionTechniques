#ifndef GJK_COLLIDER_H
#define GJK_COLLIDER_H

// ABSTRACT CLASS
#include "Collider.h" // NOTE: Use for Difference

// NEEDE INCLUDE(s)
#include "Structures.h"
#include "Constants.h"
#include "Vector.h"

// CASES FOR INTERSECTION
// A Tetrahedron
// A Triangle
// A Line

// KEY NOTE:
// - Minokwaski Difference / Sum
// - Combined Hull of Points
// - Distance Calculations

// SIMPLEX:
// n + 1 Vertices (n being the dimension)

class GJKCollider
{
private:

	Vector3 m_Vertices;
	Simplex m_OutSimplex;

public:

	// CLASS FUNCTION(s)
	GJKCollider();
	~GJKCollider();

	// BASE FUNCTION(s)
	bool GJKCollision(Collider* colliderA, Collider* colliderB);
	bool NextSimplex(Simplex& points, Vector3& direction);
	

	// GETTER FUNCTION(s)
	Simplex GetSimplex() { return m_OutSimplex; }


	// EXTRA FUNCTION(s)
	bool Line(Simplex& points, Vector3& direction);
	bool Triangle(Simplex& points, Vector3& direction);
	bool Tetrahedron(Simplex& points, Vector3& direction);

	// HELPER FUNCTION(s)
	bool SameDirection(Vector3 direction, Vector3 Ao);
	Vector3 Support(Collider* colliderA, Collider* colliderB, Vector3 direction);
};

#endif

