#include "ConvexHull.h"

ConvexHull::ConvexHull()
{


}

ConvexHull::ConvexHull(const ConvexHull& o)
{
	m_Indices = o.m_Indices;
	if (o.m_OptimizedVertexBuffer)
	{
		m_OptimizedVertexBuffer.reset(new std::vector<Vector3>(*o.m_OptimizedVertexBuffer));
		m_Vertices = VertexDataSource(*m_OptimizedVertexBuffer);
	}
	else
	{

	}


}

ConvexHull::~ConvexHull()
{



}
