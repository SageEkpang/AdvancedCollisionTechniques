#include "RayCollider.h"
#include "GameObjectEntity.h"

RayCollider::RayCollider(Vector3 origin, Vector3 direction)
{
	m_Origin = origin;
	m_Direction = direction;
}

RayCollider::RayCollider(Vector3 origin, float x_d, float y_d, float z_d)
{
	m_Origin = origin;
	m_Direction = Vector3(x_d, y_d, z_d);
}

RayCollider::RayCollider()
{
	m_Origin = Vector3(0, 0, 0);
	m_Direction = Vector3(0, 0, 0);
}

void RayCollider::Construct(Vector3 origin, Vector3 direction)
{
	m_Origin = origin;
	m_Direction = direction;
}

void RayCollider::Construct(Vector3 origin, float x_d, float y_d, float z_d)
{
	m_Origin = origin;
	m_Direction = Vector3(x_d, y_d, z_d);
}
