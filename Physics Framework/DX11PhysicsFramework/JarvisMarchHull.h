#pragma once
#ifndef JARVIS_MARCH_HULL_H
#define JARVIS_MARCH_HULL_H

#include "Collider.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// NOTE: Basically a Line

class JarvisMarchHull
{
private:

	std::vector<Vector3> m_PointCluster; // INPUT
	std::vector<Face> t_ConvexHull; // OUTPUT;
	
private:

	// BASE FUNCTION(s)
	void BuildConvexHull(std::vector<Vector3> clusterOfPoints);

public:

	// CLASS FUNCTION(s)
	JarvisMarchHull(std::vector<Vector3> clusterOfPoints);
	~JarvisMarchHull();




	// HELPER FUNCTION(s)
	Vector3 PivotAroundEdge(Vector3 edge, std::vector<Vector3> point);
	Edge OutwardsPoints(Edge edge, std::vector<Vector3> points);


};

#endif

