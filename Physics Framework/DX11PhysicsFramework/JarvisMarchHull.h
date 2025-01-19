#pragma once
#ifndef JARVIS_MARCH_HULL_H
#define JARVIS_MARCH_HULL_H

#include "Collider.h"

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

// NOTE: Basically a Line
typedef struct Edge
{
	Vector3 edgeStart;
	Vector3 edgeEnd;

	Edge(Vector3 edgeStart = Vector3(), Vector3 edgeEnd = Vector3())
	{
		this->edgeStart = edgeStart;
		this->edgeEnd = edgeEnd;
	}

	Edge(const Edge& value)
	{
		this->edgeStart = value.edgeStart;
		this->edgeEnd = value.edgeEnd;
	}

	Edge operator =(Edge value)
	{
		this->edgeStart = value.edgeStart;
		this->edgeEnd = value.edgeEnd;

		return *this;
	}

	bool operator ==(Edge value)
	{
		bool t_TempStart = this->edgeStart == value.edgeStart ? true : false;
		bool t_TempEnd = this->edgeEnd == value.edgeEnd ? true : false;

		return (t_TempStart && t_TempEnd);
	}

}Edge3D;

typedef struct Face // REFERRING TO A TRIANGLE FACE (CW or CWW)
{
	Vector3 v1;
	Vector3 v2;
	Vector3 v3;

	Face(Vector3 v1 = Vector3(), Vector3 v2 = Vector3(), Vector3 v3 = Vector3())
	{
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
	}
	
	Face(const Face& value)
	{
		this->v1 = value.v1;
		this->v2 = value.v2;
		this->v3 = value.v3;
	}

	Face operator =(Face value)
	{
		this->v1 = value.v1;
		this->v2 = value.v2;
		this->v3 = value.v3;

		return *this;
	}

}Face3D;


class JarvisMarchHull
{
private:

	std::vector<Vector3> m_PointCluster; // INPUT
	
public:

	// CLASS FUNCTION(s)
	JarvisMarchHull(std::vector<Vector3> clusterOfPoints);
	~JarvisMarchHull();


	// BASE FUNCTION(s)
	void BuildConvexHull(std::vector<Vector3> clusterOfPoints);


	// HELPER FUNCTION(s)
	Vector3 PivotAroundEdge(Vector3 edge, std::vector<Vector3> point);



};

#endif

