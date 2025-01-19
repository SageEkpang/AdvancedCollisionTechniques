#include "QuickHullCollider.h"


QuickHullCollider::QuickHullCollider(std::vector<Vector3> clusterOfPoints)
{
	m_PointCluster.insert(m_PointCluster.end(), clusterOfPoints.begin(), clusterOfPoints.end());
	BuildConvexHull(m_PointCluster);
}


QuickHullCollider::~QuickHullCollider()
{
	m_PointCluster.clear();
	m_ConvexHull.clear();
}

std::vector<Vector3> QuickHullCollider::BuildInitGeometry(std::vector<Vector3> points)
{
	std::vector<Vector3> t_TempPoints;
	t_TempPoints.insert(t_TempPoints.end(), points.begin(), points.end());


	// STEP


	return std::vector<Vector3>();
}


std::vector<Vector3> QuickHullCollider::BuildConvexHull(std::vector<Vector3> clusterOfPoints)
{
	// STEP 1: Make init Geometry
	BuildInitGeometry(clusterOfPoints);


	// STEP 2: Connecting Points and Planes in 3D Quick Hull



}

