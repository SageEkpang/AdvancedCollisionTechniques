#pragma once
#ifndef QUICK_HULL_H
#define QUICK_HULL_H

// ABSTRACT INCLUDE(s)
#include "Collider.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

/*
NOTE:
- Oriented Hyper Plan through d points 
- Signed distance to hyperplane

---

- Let H be a convex hull in (R)d
- Let p be a point in (R)d
- F is a facet of conv(p U H) if and only if, (F is a facet of H and p is below F) or (F is not a facet of H and its vertices are p and the vertices of a ridge)
of H with one incident facet below p and the other incident facet above p

- When quick hull creates a cone of new facets, it builds new outside sets from the outside sets of the visible facets

*/

struct Facet
{
	int id;
	std::vector<Vector3> childPoints;
};

class QuickHullCollider
{
private: // PRIVATE VARIABLE(s)

	// Points for Construction
	std::vector<Vector3> m_InputPoints; // NOTE: Point Cloud that needs to tbe calculated
	std::vector<Vector3> m_OutputPoints; // NOTE: Output of points for the 3D Geometry Mesh

private: // PRIVATE  FUNCTION(s)

	// BASE FUNCTION(s)
	std::vector<Vector3> BuildConvexHull(std::vector<Vector3> points);

public:

	// CLASS FUNCTION(s)
	QuickHullCollider(std::vector<Vector3> points);
	~QuickHullCollider();

	// GETTER FUNCTION(s)
	std::vector<Vector3> GetInputPoints() { return m_InputPoints; }
	std::vector<Vector3> GetOutputPoints() { return m_OutputPoints; }
};

#endif
