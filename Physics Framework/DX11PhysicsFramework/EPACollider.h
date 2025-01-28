#pragma once
#ifndef EPA_COLLIDER_H
#define EPA_COLLIDER_H

// ABSTRACT CLASS(s)
#include "Collider.h"


// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

class EPACollider
{
private:


public:

	// CLASS FUNCTION(s)
	EPACollider();
	~EPACollider();


	// BASE FUNCTION(s)
	CollisionManifold EPACollision(Simplex& simplex, Collider* colliderA, Collider* colliderB);

	// HELPER FUNCTION(s)
	bool SameDirection(Vector3 direction, Vector3 Ao);
	Vector3 Support(Collider* colliderA, Collider* colliderB, Vector3 direction);
	void AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges, std::vector<size_t> faces, size_t a, size_t b);
	std::pair<std::vector<Vector4>, size_t> GetFaceNormals(std::vector<Vector3> polytope, std::vector<size_t> faces);

};

#endif