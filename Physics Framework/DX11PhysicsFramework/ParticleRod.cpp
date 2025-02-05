#include "ParticleRod.h"

// NOTE: Set Restitution to 0
CollisionManifold ParticleRod::ParticleRodSimulation(Particle* particleA, Particle* particleB) // TODO: Pass in the Particles as collider arguements
{
    // NOTE: Length = Desired Length
    // NOTE: CurrentLength = CurrentLength of the Rod
    float t_CurrentLength = GetCurrentLength(); // Magnitude from the other particle

    // Magnitude(PosB - PosA) = Length / Distance

    // NOTE: Do not need to do rod physics due to the length being the same
    if (t_CurrentLength == m_Length) 
    { 
        return false; 
    }

    // NOTE: Calculate Normal
    Vector3 t_Normal = particleB->GetTransform()->GetPosition() - particleA->GetTransform()->GetPosition();
    t_Normal = t_Normal.Normalise();

    // NOTE: Contact Normal Depends on Whether we're extending or Compressing
    if (t_CurrentLength > m_Length)
    {
        m_CollisionManifold.collisionNormal = t_Normal;
        m_CollisionManifold.penetrationDepth = t_CurrentLength - m_Length;
    }
    else
    {
        m_CollisionManifold.collisionNormal = t_Normal - 1;
        m_CollisionManifold.penetrationDepth = m_Length - t_CurrentLength;
    }
    
    return true;
}
