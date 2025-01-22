#pragma once
#ifndef QUICK_HULL_H
#define QUICK_HULL_H

// ABSTRACT INCLUDE(s)
#include "Collider.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

class QuickHullCollider
{
private: // PRIVATE VARIABLE(s)

	// Points for Construction
	std::vector<Vector3> m_PointCluster; // NOTE: Point Cloud that needs to tbe calculated
	std::vector<Face> m_ConvexHull;

private: // PRIVATE  FUNCTION(s)

	// BASE FUNCTION(s)
	std::vector<Vector3> BuildConvexHull(std::vector<Vector3> clusterOfPoints);

public:

	// CLASS FUNCTION(s)
	QuickHullCollider(std::vector<Vector3> clusterOfPoints);
	~QuickHullCollider();




	// HELPER FUNCTION(s)
	std::vector<Vector3> BuildInitGeometry(std::vector<Vector3> points);



};

#endif
