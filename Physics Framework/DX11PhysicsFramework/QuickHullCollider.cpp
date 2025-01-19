#include "QuickHullCollider.h"

QuickHullCollider::QuickHullCollider(std::vector<Vector3> points)
{
	m_InputPoints.insert(m_InputPoints.end(), points.begin(), points.end());


	// Building the Convex Hull of the 3D Shape
	BuildConvexHull(points);
}

QuickHullCollider::~QuickHullCollider()
{
	m_InputPoints.clear();
	m_OutputPoints.clear();
}

// F = Facet (May have to be an array of 3x3 points)
// p = Point
// d + 1 = 
// Simplex = Triangle or Tetrahedron to Arbitrary Dimensions (3D - Tetrahedron)
// v1, v2, v3, v4 Is the starting simplex for the Quick Hull

std::vector<Vector3> QuickHullCollider::BuildConvexHull(std::vector<Vector3> points)
{
	// Make Sure the Points are clear before inserting the Points happens
	m_OutputPoints.clear();
	std::vector<Vector3> t_Facets = {};

	std::vector<Vector3> t_OutsideSet;
	std::vector<Vector3> t_InsideSet;

	for (auto& facet : t_Facets)
	{
		for (auto& p : m_InputPoints)
		{
			if (p > facet)
			{
				t_OutsideSet.push_back(p);
			}

		}
	}

	// for (auto& )










	return std::vector<Vector3>();
}
