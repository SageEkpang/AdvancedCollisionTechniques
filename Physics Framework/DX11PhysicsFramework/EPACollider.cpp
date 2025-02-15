#include "EPACollider.h"

EPACollider::EPACollider()
{



}

EPACollider::~EPACollider()
{

}

CollisionManifold EPACollider::EPACollision(Simplex& simplex, Collider& colliderA, Collider& colliderB)
{
	std::vector<Vector3> t_Polytope;
	t_Polytope.insert(t_Polytope.end(), simplex.begin(), simplex.end());

	// NOTE: Potential Face / Triangle list, in terms of Winding order
	std::vector<size_t> t_Faces = {

		0, 1, 2,
		0, 3, 1,
		0, 2, 3,
		1, 3, 2
	};

	// NOTE: n-Polytope of the face, Minimum face normal
	// NOTE: Calculates the new normals of the Face
	auto [t_Normals, t_MinFace] = GetFaceNormals(t_Polytope, t_Faces); // TODO: May need to move this into the loop

	Vector3 t_MinNormal;
	float t_MinDistance = FLT_MAX;

	t_MinNormal = t_Normals[t_MinFace].xyz();
	t_MinDistance = t_Normals[t_MinFace].w;

	Vector3 t_Support = Support(colliderA, colliderB, t_MinNormal);
	float t_Distance = Vector::CalculateDotProductNotNorm(t_MinNormal, t_Support);

	if (std::abs(t_Distance - t_MinDistance) > 0.001f)
	{
		t_MinDistance = FLT_MAX;
		std::vector<std::pair<size_t, size_t>> t_UniqueEdges;

		for (size_t i = 0; i < t_Normals.size(); i++)
		{
			if (SameDirection(t_Normals[i].xyz(), t_Support))
			{
				size_t t_F = i * 3;

				AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F,     t_F + 1);
				AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F + 1, t_F + 2);
				AddIfUniqueEdge(t_UniqueEdges, t_Faces, t_F + 2, t_F);

				t_Faces[t_F + 2] = t_Faces.back(); t_Faces.pop_back();
				t_Faces[t_F + 1] = t_Faces.back(); t_Faces.pop_back();
				t_Faces[t_F    ] = t_Faces.back(); t_Faces.pop_back();

				t_Normals[i] = t_Normals.back();
				t_Normals.pop_back();

				i--;
			}
		}

		std::vector<size_t> t_NewFaces;
		for (auto [edgeIndex1, edgeIndex2] : t_UniqueEdges)
		{
			t_NewFaces.push_back(edgeIndex1);
			t_NewFaces.push_back(edgeIndex2);
			t_NewFaces.push_back(t_Polytope.size());
		}

		t_Polytope.push_back(t_Support);

		auto [t_NewNormals, t_NewMinFace] = GetFaceNormals(t_Polytope, t_NewFaces);

		float t_OldMinDistance = FLT_MAX;
		for (size_t i = 0; i < t_Normals.size(); i++)
		{
			if (t_Normals[i].w < t_OldMinDistance)
			{
				t_OldMinDistance = t_Normals[i].w;
				t_MinFace = i;
			}
		}

		if (t_NewNormals[t_NewMinFace].w < t_OldMinDistance)
		{
			t_MinFace = t_NewMinFace + t_Normals.size();
		}

		t_Faces.insert(t_Faces.end(), t_NewFaces.begin(), t_NewFaces.end());
		t_Normals.insert(t_Normals.end(), t_NewNormals.begin(), t_NewNormals.end());
	}

	CollisionManifold t_Points;
	
	t_Points.collisionNormal = t_MinNormal;
	t_Points.penetrationDepth = t_MinDistance + 0.001f;
	t_Points.hasCollision = true;
	t_Points.contactPointCount = 1.0;

	return t_Points;
}

bool EPACollider::SameDirection(Vector3 direction, Vector3 Ao)
{
	return Vector::CalculateDotProductNotNorm(direction, Ao) > 0;
}

Vector3 EPACollider::Support(Collider& colliderA, Collider& colliderB, Vector3 direction)
{
	// REWORK: Rework the collider class so it knows what vertices it has, this is used for this function
	Vector3 t_TempA = colliderA.FindFurthestPoint(direction);
	Vector3 t_TempB = colliderB.FindFurthestPoint(-direction); // TODO: Need to actually check if it is working

	return t_TempA - t_TempB;
}

void EPACollider::AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges, std::vector<size_t>& faces, size_t a, size_t b)
{
	// NOTE: Checks if the reverse of the edge already exists in the list, if so, remove said list
	auto t_Reverse = std::find(edges.begin(), edges.end(), std::make_pair(faces[b], faces[a]));

	if (t_Reverse != edges.end())
	{
		edges.erase(t_Reverse);
	}
	else
	{
		edges.emplace_back(faces[a], faces[b]);
	}
}

std::pair<std::vector<Vector4>, size_t> EPACollider::GetFaceNormals(std::vector<Vector3>& polytope, std::vector<size_t>& faces)
{
	// NOTE: Get the Array of Normal Faces
	std::vector<Vector4> t_NormalArray;
	size_t t_MinTriangle = 0;
	float t_MinDistance = FLT_MAX;

	for (size_t i = 0; i < faces.size(); i += 3)
	{
		Vector3 t_A = polytope[faces[i]];
		Vector3 t_B = polytope[faces[i + 1]];
		Vector3 t_C = polytope[faces[i + 2]];

		Vector3 t_Normal = Vector::Normalise(Vector::CalculateCrossProductV(t_B - t_A, t_C - t_A));
		float t_Distance = Vector::CalculateDotProductNotNorm(t_Normal, t_A);

		if (t_Distance < 0)
		{
			t_Normal *= -1;
			t_Distance *= -1;
		}

		Vector4 t_TempNorm = Vector4(t_Normal.x, t_Normal.y, t_Normal.z, t_Distance);
		t_NormalArray.emplace_back(t_TempNorm);

		if (t_Distance < t_MinDistance)
		{
			t_MinTriangle = i / 3;
			t_MinDistance = t_Distance;
		}
	}
	
	std::pair<std::vector<Vector4>, size_t> t_Ps;
	t_Ps = std::make_pair(t_NormalArray, t_MinTriangle);

	return t_Ps;
}
