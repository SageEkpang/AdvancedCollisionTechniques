#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

// ABSTRACT CLASS(s)
#include "ColliderEntity.h"

class BoxCollider : public ColliderEntity
{
public:

	Vector3 m_Offset;
	Vector3 m_Scale;

public:

	// CLASS FUNCTION(s) (General)
	BoxCollider(Vector3 offset, Vector3 scale);
	BoxCollider(Vector3 offset, float width, float height, float length);
	BoxCollider(float x_scale, float y_scale, float z_scale);
	BoxCollider(Vector3 scale);
	BoxCollider(float x_offset, float y_offset, float z_offset, float width, float height, float length);

	// CLASS FUNCTION(s) (Components)
	BoxCollider();
	~BoxCollider() override { }

	void Construct(Vector3 offset, Vector3 scale, ID3D11Device* device);
	void Construct(Vector3 offset, float width, float height, float length, ID3D11Device* device);
	void Construct(float x_scale, float y_scale, float z_scale, ID3D11Device* device);
	void Construct(Vector3 scale, ID3D11Device* device);
	void Construct(float x_offset, float y_offset, float z_offset, float width, float height, float length, ID3D11Device* device);

	// BASE FUNCTION(s)
	void Update(float deltaTime) override;


	// GETTER FUNCTION(s)
	Vector3 GetMax();
	Vector3 GetMin();
	inline const Vector3 GetExtents() { return m_Scale; }
	inline Vector3 GetHalfExtents() { return m_Scale / 2; }
	Interval GetInterval(Vector3 axis);
};

#endif
