#pragma once
#ifndef HALF_EDGE_MESH_H
#define HALF_EDGE_MESH_H

#include "Constants.h"
#include "Structures.h"

template<typename FloatType, typename IndexType>
class HalfEdgeMesh
{
public:

	struct HalfEdge
	{
		IndexType endVertex;
		IndexType opp;
		IndexType face;
		IndexType next;
	};

	struct FaceAlt
	{
		IndexType halfEdgeIndex; // Index of one of the half edges of this face
	};

	std::vector<Vector3> m_vertices;
	std::vector<FaceAlt> m_faces;
	std::vector<HalfEdge> m_halfEdges;

	// HalfEdgeMesh(const )





};

#endif