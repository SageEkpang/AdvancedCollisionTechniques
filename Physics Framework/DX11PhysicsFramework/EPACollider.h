#ifndef EPA_COLLIDER_H
#define EPA_COLLIDER_H

// ABSTRACT CLASS(s)
#include "ColliderEntity.h"
#include "Vector3.h"

class EPACollider : public ColliderEntity
{
public:

	std::vector<Vector3> m_Vertices;
	std::vector<Vector3> m_PositionStore;

public:

	// CLASS FUNCTION(s) (Components)
	EPACollider();
	~EPACollider() override;

	void Construct(std::string path, ID3D11Device* device);
	void ConstructHull(std::string filepath, ID3D11Device* device);

	// BASE FUNCTION(s)
	void Update(float deltaTime) override;
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device) override;

private:

	// HELPER FUNCTION(s)
	void FillVerticesArray(char* path);
};

#endif