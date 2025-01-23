#pragma once
#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include "Constants.h"
#include "Structures.h"

#include "MeshBuilder.h"

// template<typename T>
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
	ConvexHull(ConvexHull&& o);
	// ConvexHull(const MeshBuilder<T>& mesh, const VertexDataSource& pointCloud, bool CCW, bool useOriginalIndices);
	~ConvexHull();


	// BASE FUNCTION(s)

	ConvexHull& operator=(const ConvexHull& o)
	{
		if (&o == this)
		{
			return *this;
		}

		m_Indices = o.m_Indices;

		if (o.m_OptimizedVertexBuffer)
		{
			m_OptimizedVertexBuffer.reset(new std::vector<Vector3>(*o.m_OptimizedVertexBuffer));
			m_Vertices = VertexDataSource(*m_OptimizedVertexBuffer);
		}
		else
		{
			m_Vertices = o.m_Vertices;
		}
	}

	ConvexHull& operator=(ConvexHull&& o)
	{
		if (&o == this) {
			return *this;
		}
		m_Indices = std::move(o.m_Indices);
		if (o.m_OptimizedVertexBuffer) {
			m_OptimizedVertexBuffer = std::move(o.m_OptimizedVertexBuffer);
			o.m_Vertices = VertexDataSource();
			m_Vertices = VertexDataSource(*m_OptimizedVertexBuffer);
		}
		else 
		{
			m_Vertices = o.m_Vertices;
		}
		return *this;
	}









};


#endif