#pragma once
#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include "Constants.h"
#include "Structures.h"

#include "MeshBuilder.h"

class ConvexHull
{
private:

	std::unique_ptr<std::vector<Vector3>> m_OptimizedVertexBuffer;
	VertexDataSource m_Vertices;
	std::vector<size_t> m_Indices;

public:

	// CLASS FUNCTION(s)
	ConvexHull();
	ConvexHull(const ConvexHull& o);
	~ConvexHull();


	// BASE FUNCTION(s)

	ConvexHull& operator=(const ConvexHull& o)
	{
		if (&o == this)
		{
			return *this;
		}

		m_Indices = o.m_Indices;


	}












};


#endif