#include "PhysicsEntity.h"
#include "GameObjectEntity.h"

PhysicsEntity::PhysicsEntity()
{
	m_Velocity = Vector3(0.f, 0.f, 0.f);
}

PhysicsEntity::~PhysicsEntity()
{
	
}

void PhysicsEntity::CalculateAcceleration(float deltaTime)
{
	// Add NetForce to Acceleration
	m_Acceleration += m_NetForce; // / m_Mass

	// Get position and add it to the velocity of the object
	Vector3 t_Position = m_Owner->m_Transform.m_Position;
	m_Velocity += m_Acceleration * deltaTime;

	// Change position based on velocity and set new position based on velocity
	t_Position += m_Velocity * deltaTime;
	m_Owner->m_Transform.m_Position = t_Position;
}

void PhysicsEntity::Update(float deltaTime)
{
	if (m_Mass == 0) return;

	// NET FORCE ACCUMULATION
	if (m_SimulateGravity) { m_NetForce += GravityForce(); }
	if (m_SimulateDrag) { m_NetForce += DragForce(); }
	if (m_SimulateFriction) { m_NetForce += FrictionForce(); }

	CalculateAcceleration(deltaTime);

	m_NetForce = VECTOR3_ZERO;
	m_Acceleration = VECTOR3_ZERO;
}

void PhysicsEntity::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{

}

Vector3 PhysicsEntity::FrictionForce()
{
	if (m_Velocity == 0.f) { return Vector3(0.f, 0.f, 0.f); }

	Vector3 t_CopyVelocity = m_Velocity;
	Vector3 t_CalculatedFriction = t_CopyVelocity.Pow(2) * m_Friction;
	float t_Friction = t_CalculatedFriction.Magnitude();

	Vector3 pm_CalculatedFriction;
	pm_CalculatedFriction = t_CopyVelocity * -1;
	pm_CalculatedFriction = pm_CalculatedFriction.Normalise() * t_Friction;
	pm_CalculatedFriction = Vector3(pm_CalculatedFriction.x, pm_CalculatedFriction.y, pm_CalculatedFriction.z);

	return pm_CalculatedFriction;
}

Vector3 PhysicsEntity::DragForce()
{
	// Check if the value is more than 0, do not want to divide by 0
	if (m_Velocity == 0) { return Vector3(0, 0, 0); }

	Vector3 t_CopyVelocity = m_Velocity;

	// Calculate drag using the fluid density, velocity squared, drag coefficient and cross sectional area
	float t_DensityOfFluid = 0.9; // Density of Air 
	Vector3 t_CalculateDrag = t_DensityOfFluid * (t_CopyVelocity.Pow(2) * 0.5f) * m_Drag * 1;
	float t_Drag = t_CalculateDrag.Magnitude();

	// NOTE: Intergrate Drag
	Vector3 pm_CalculatedDrag = t_CopyVelocity * -1;
	pm_CalculatedDrag = pm_CalculatedDrag.Normalise() * t_Drag;
	pm_CalculatedDrag = Vector3(pm_CalculatedDrag.x, t_CopyVelocity.y, t_CopyVelocity.z);

	return pm_CalculatedDrag;
}

// NOTE: Gravity Formula changed to be more simpler relative to objects
Vector3 PhysicsEntity::GravityForce()
{
	// Calculate the Distance from Object to Ground (0, 0, 0 will always be the ground)
	Vector3 t_Gravity = GetGravity() * m_Mass * -1; // NOTE: Simplified Gravity Formula
	return t_Gravity;
}

Vector3 PhysicsEntity::TensionForce()
{
	//Vector3 t_Tension = (m_Mass * GetGravity()) + (m_Mass * m_Acceleration);

	//Vector3 t_CopyVelocity = m_Velocity * -1;
	//t_CopyVelocity = Vector::Normalise(t_CopyVelocity) * t_Tension; // TODO: Make sure that this works in the future

	return Vector3();
}

float PhysicsEntity::GetDensity()
{
	float Volume = m_Owner->m_Transform.m_Scale.x * m_Owner->m_Transform.m_Scale.y * m_Owner->m_Transform.m_Scale.z;
	return m_Mass / Volume;
}
