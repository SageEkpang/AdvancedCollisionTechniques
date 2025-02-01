#include "SphereCollider.h"
#include "BoxCollider.h"
#include "PlaneCollider.h"
#include "OBBCollider.h"

bool SphereCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
    Vector3 DistanceBetweenPoints = other.GetPosition() - GetPosition(); // may need to flip this
    float CombinedRadius = m_Radius + other.m_Radius;

    if (Vector::Magnitude(DistanceBetweenPoints) < (CombinedRadius))
    {
        out.collisionNormal = Vector::Normalise(other.GetPosition() - GetPosition()); // Normal
        out.contactPointCount = 1;
        out.points[0].position = GetPosition() + (out.collisionNormal * GetRadius());
        out.penetrationDepth = fabs(Vector::Magnitude(DistanceBetweenPoints) - CombinedRadius); // Pen Depth
        return true;
    }

    return false;
}

bool SphereCollider::CollidesWith(BoxCollider& other, CollisionManifold& out)
{
    Vector3 TempPos = GetPosition();
    float TempRadius = m_Radius;
    float TotalRadius = Vector::Magnitude(other.NearestPoint(GetPosition())) - m_Radius;

    // Minimum Distance Temp Variable
    float DistanceMin = 0;

    Vector3 OtherMax = other.GetPosition() + other.GetScale();
    Vector3 OtherMin = other.GetPosition() - other.GetScale();

    // Check the Distance of the Circle Position from the Box position and extents
    if (TempPos.x < OtherMin.x) DistanceMin += std::powf(TempPos.x - OtherMin.x, 2);
    else if (TempPos.x > OtherMax.x) DistanceMin += std::powf(TempPos.x - OtherMax.x, 2);

    if (TempPos.y < OtherMin.y) DistanceMin += std::powf(TempPos.y - OtherMin.y, 2);
    else if (TempPos.y > OtherMax.y) DistanceMin += std::powf(TempPos.y - OtherMax.y, 2);

    if (TempPos.z < OtherMin.z) DistanceMin += std::powf(TempPos.z - OtherMin.z, 2);
    else if (TempPos.z > OtherMax.z) DistanceMin += std::powf(TempPos.z - OtherMax.z, 2);

    // Another Way of Calculating it
    //Vector3 t_NearestPoint = other.NearestPoint(GetPosition());
    //float t_DistanceSqrt = std::pow(Vector::Magnitude(GetPosition() - t_NearestPoint), 2);
    //float t_RadiusSqrt = m_Radius * m_Radius;
    //return t_DistanceSqrt < t_RadiusSqrt;

    // Check if the Distance of the Circle is in the Box's "Radius"
    if (DistanceMin <= (std::powf(TempRadius, 2)))
    {
        out.collisionNormal = Vector::Normalise(GetPosition() - other.GetPosition());
        out.contactPointCount = 1;
        out.hasCollision = true;
        out.points[0].position = GetPosition() + (out.collisionNormal * GetRadius());


        int t_AverageScale = abs(other.GetScale().x + other.GetScale().y + other.GetScale().z / 3);
        out.penetrationDepth = fabs(Vector::Magnitude(other.GetPosition() - GetPosition()) - t_AverageScale);
        return true;
    }

    return false;
}

bool SphereCollider::CollidesWith(PlaneCollider& other, CollisionManifold& out)
{
    Vector3 ClosestPoint = other.NearestPoint(GetPosition());
    float t_Distance = Vector::Magnitude(Vector::DistanceTo(ClosestPoint, GetPosition()));
    float t_Radius = std::pow(m_Radius, 2);

    // Alternative equation
    //Vector3 t_NearestPoint = other.NearestPoint(GetPosition());
    //float t_DistanceSqrt = std::pow( Vector::Magnitude(GetPosition() - t_NearestPoint), 2);
    //return t_Distance < t_Radius;

    if (t_Distance <= t_Radius)
    {
        out.collisionNormal = other.GetPlaneNormal();
        out.contactPointCount = 1;
        Vector3 ClosestPoint = NearestPoint(other.GetPosition());
        out.points[0].penetrationDepth = fabs(Vector::Magnitude(GetPosition() - ClosestPoint));
        return true;
    }

    return false;
}

bool SphereCollider::CollidesWith(OBBCollider& other, CollisionManifold& out)
{
    Vector3 t_NearestPoint = other.NearestPoint(GetPosition());
    float t_DistanceSqrt = std::pow(Vector::Magnitude(GetPosition() - t_NearestPoint), 2);
    float t_RadiusSqrt = m_Radius * m_Radius;
    return t_DistanceSqrt < t_RadiusSqrt;
}

Vector3 SphereCollider::NearestPoint(Vector3 point) // Point and Sphere
{
    Vector3 t_SphereToPoint = Vector::Normalise(point - GetPosition());
    t_SphereToPoint *= GetRadius();
    return t_SphereToPoint + GetPosition();
}

bool SphereCollider::PointInSphere(Vector3 point)
{
    float t_MagnitudeSquared = std::pow(Vector::Magnitude(point - GetPosition()), 2);
    float t_RadiusAmount = m_Radius * m_Radius;
    return t_MagnitudeSquared < t_RadiusAmount;
}
