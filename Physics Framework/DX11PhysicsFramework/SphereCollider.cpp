#include "SphereCollider.h"

Vector3 SphereCollider::NearestPoint(Vector3 point) // Point and Sphere
{
    /*Vector3 t_SphereToPoint = Vector::Normalise(point - GetPosition());
    t_SphereToPoint *= GetRadius();*/
    // return t_SphereToPoint + GetPosition();
    return Vector3();
}

bool SphereCollider::PointInSphere(Vector3 point)
{
    //float t_MagnitudeSquared = std::pow(Vector::Magnitude(point - GetPosition()), 2);
    //float t_RadiusAmount = m_Radius * m_Radius;
    // return t_MagnitudeSquared < t_RadiusAmount;
    return true;
}
