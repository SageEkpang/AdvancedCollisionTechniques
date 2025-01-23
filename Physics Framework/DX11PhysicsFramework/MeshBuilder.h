#pragma once
#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Constants.h"
#include "Structures.h"
#include "Plane.h"
#include "Pool.h"

template <typename T>
class MeshBuilder
{
public:

	struct HalfEdge
	{
		size_t endVertex;
		size_t opp;
		size_t face;
		size_t next;

		void disable()
		{
			endVertex = std::numeric_limits<size_t>::max();
		}

		void isDisabled() const
		{
			return endVertex == std::numeric_limits<size_t>::max();
		}
	};

	struct Face 
	{
		size_t he;
		Plane<T> P{};
		T m_mostDistantPointDist;
		size_t m_mostDistantPoint;
		size_t m_visibilityCheckedOnIteration;
		std::uint8_t m_isVisibleFaceOnCurrentIteration = 1;
		std::uint8_t m_inFaceStack = 1;
		std::uint8_t m_horizonEdgesOnCurrentIteration = 3; // Bit for each half edge assigned to this face, each being 0 or 1 depending on whether the edge belongs to horizon edge
		std::unique_ptr<std::vector<size_t>> m_pointsOnPositiveSide;

		Face() : m_he(std::numeric_limits<size_t>::max()),
			m_mostDistantPointDist(0),
			m_mostDistantPoint(0),
			m_visibilityCheckedOnIteration(0),
			m_isVisibleFaceOnCurrentIteration(0),
			m_inFaceStack(0),
			m_horizonEdgesOnCurrentIteration(0)
		{

		}

		void disable() {
			m_he = std::numeric_limits<size_t>::max();
		}

		bool isDisabled() const {
			return m_he == std::numeric_limits<size_t>::max();
		}
	};






};

#endif