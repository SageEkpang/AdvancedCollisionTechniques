#include "JarvisMarchHull.h"

JarvisMarchHull::JarvisMarchHull(std::vector<Vector3> clusterOfPoints)
{
	m_PointCluster.insert(m_PointCluster.end(), clusterOfPoints.begin(), clusterOfPoints.end());
	BuildConvexHull(m_PointCluster);
}

JarvisMarchHull::~JarvisMarchHull()
{




}

Vector3 JarvisMarchHull::PivotAroundEdge(Vector3 edge, std::vector<Vector3> point)
{
	Vector3 t_Point = point[0];


	return Vector3();
}

Edge JarvisMarchHull::OutwardsPoints(Edge edge, std::vector<Vector3> points)
{
	// Find outmost point relative to edge


	for (int i = 0; i < points.size(); ++i)
	{

		if (edge.edgeStart == edge.edgeEnd)
		{
			return Edge(edge.edgeStart, points[i]);
		}
		



	}


	return 0;
}

void JarvisMarchHull::BuildConvexHull(std::vector<Vector3> clusterOfPoints)
{
	std::vector<Vector3> t_Output;
	float t_SmallestZ = clusterOfPoints[0].z;
	int t_PointIndex = 0;

	// STEP 1: Find point with the Smallest Z Value
	for (int i = 1; i < clusterOfPoints.size(); ++i)
	{
		if (t_SmallestZ < clusterOfPoints[i].z)
		{
			t_SmallestZ = clusterOfPoints[i].z;
			t_PointIndex = i;
		}
	}

	// STEP 2: Find the point q that makes the largest angle with the z-axis from p
	Vector3 t_LargestAngle = Vector3();
	float t_CalculateDot = Vector::CalculateDotProduct(clusterOfPoints[t_PointIndex], clusterOfPoints[0]);
	int t_LargestIndex = 0;

	for (int i = 0; i < clusterOfPoints.size(); ++i)
	{
		// Check if we are checking the same value, if we are, skip iteration
		if (i == t_PointIndex) { continue; }

		float t_TempDot = Vector::CalculateDotProduct(clusterOfPoints[t_PointIndex], clusterOfPoints[i]);

		// See if the angle is large enough, if its is, set the newly calculated angle to that
		if (t_TempDot > t_CalculateDot)
		{
			t_CalculateDot = t_TempDot;
			t_LargestAngle = clusterOfPoints[i];
			t_LargestIndex = i;
		}
	}

	// STEP 3: Init the Search Queue (The edge that makes up "p, q")
	std::vector<Edge> t_SearchQue;
	t_SearchQue.push_back(Edge(clusterOfPoints[t_PointIndex], clusterOfPoints[t_LargestIndex])); // Inserting the Edges into the Search Que array
	
	Face t_TempFace;
	// STEP 4: Search for the Different Points that make the Convex Hull

	srand(time(NULL));

	do
	{
		int t_RandomIndex = rand() % t_SearchQue.size();








	} while (!t_SearchQue.empty());





}
