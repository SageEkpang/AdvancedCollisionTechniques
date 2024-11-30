#include "SphereCollider.h"
#include "BoxCollider.h"
#include "PlaneCollider.h"

bool SphereCollider::CollidesWith(SphereCollider& other, CollisionManifold& out)
{
    Vector3 DistanceBetweenPoints = other.GetPosition() - GetPosition();
    float CombinedRadius = m_Radius + other.m_Radius;

    if (Vector::Magnitude(DistanceBetweenPoints) < CombinedRadius)
    {
        out.collisionNormal = Vector::Normalise(DistanceBetweenPoints); // Normal
        out.contactPointCount = 1;
        out.points[0].position = GetPosition() + (out.collisionNormal * GetRadius());
        out.points[0].penetrationDepth = fabs(Vector::Magnitude(DistanceBetweenPoints) - CombinedRadius);
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

    // Check if the Distance of the Circle is in the Box's "Radius"
    if (DistanceMin <= (std::powf(TempRadius, 2)))
    {
        out.collisionNormal = Vector::Normalise(GetPosition() - other.GetPosition());
        out.contactPointCount = 1;
        out.points[0].position = GetPosition() + (out.collisionNormal * GetRadius());
        out.points[0].penetrationDepth = GetRadius() - DistanceMin;

        return true;
    }

    return false;
}

bool SphereCollider::CollidesWith(PlaneCollider& other, CollisionManifold& out)
{
    Vector3 ClosestPoint = other.NearestPoint(GetPosition());
    float Distance = Vector::Magnitude(Vector::DistanceTo(ClosestPoint, GetPosition()));
    float t_Radius = std::pow(m_Radius, 2);

    if (Distance <= t_Radius)
    {
        out.collisionNormal = other.GetPlaneNormal();
        out.contactPointCount = 1;
        Vector3 ClosestPoint = NearestPoint(other.GetPosition());
        out.points[0].penetrationDepth = fabs(Vector::Magnitude(GetPosition() - ClosestPoint));
        return true;
    }

    return false;
}

Vector3 SphereCollider::NearestPoint(Vector3 point)
{
    Vector3 t_Distance = Vector::Normalise(point - GetPosition());
    Vector3 t_ScaledDistance = t_Distance * GetRadius();
    return t_ScaledDistance + GetPosition();
}