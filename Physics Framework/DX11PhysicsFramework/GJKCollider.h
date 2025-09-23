#ifndef GJK_COLLIDER_H
#define GJK_COLLIDER_H

// ABSTRACT CLASS
#include "ColliderEntity.h" // NOTE: Use for Difference
#include "Vector3.h"

// CASES FOR INTERSECTION
// A Tetrahedron
// A Triangle
// A Line

// KEY NOTE:
// - Minokwaski Difference / Sum
// - Combined Hull of Points
// - Distance Calculations

// SIMPLEX:
// n + 1 Vertices (n being the dimension)

class GJKCollider : public ColliderEntity
{
public:

	std::vector<Vector3> m_Vertices;
	std::vector<Vector3> m_PositionStore;

public:

	// CLASS FUNCTION(s) (Components)
	GJKCollider();
	~GJKCollider() override;

	void Construct(char* path, ID3D11Device* device);

	// BASE FUNCTION(s)	
	void Update(float deltaTime) override;
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device) override;

	// HELPER FUNCTION(s)
	void FillVerticesArray(char* path);
};

#endif

