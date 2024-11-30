#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(Transform* transform, float mass)
{
	m_Transform = transform;
	m_Mass = mass;
}

PhysicsObject::~PhysicsObject()
{
	delete m_Transform;
}

void PhysicsObject::CalculateAcceleration(float deltaTime)
{
	// Add NetForce to Acceleration
	m_Acceleration += m_NetForce; // / m_Mass

	// Get position and add it to the velocity of the object
	Vector3 t_Position = m_Transform->GetPosition();
	m_Velocity += m_Acceleration * deltaTime;

	// Change position based on velocity and set new position based on velocity
	t_Position += m_Velocity * deltaTime;
	m_Transform->SetPosition(t_Position);
}

void PhysicsObject::Update(float deltaTime)
{
	if (m_Mass == 0) return;

	// Adding Forces to the NetForce
	if (m_SimulateGravity) { m_NetForce += GravityForce(); }
	if (m_UseDrag) { m_NetForce += DragForce(); }
	// if (m_UseFriction) { m_NetForce += FrictionForce(); }

	CalculateAcceleration(deltaTime);

	m_NetForce = VECTOR3_ZERO;
	m_Acceleration = VECTOR3_ZERO;
}

Vector3 PhysicsObject::FrictionForce()
{
	// Horizontal Friction = Force - Friction Force = m * a
	// Vertical Friction = NormalForce - Gravity * Mass = 0

	float NormalForce = m_Gravity * m_Mass;
	float CoefFric = 0.9; // Friction Coefficent
	float Friction = CoefFric * NormalForce;

	// Intergration
	Vector3 CopyVelocity = m_Velocity * -1;
	CopyVelocity = Vector::Normalise(CopyVelocity) * std::abs(Friction);
	return CopyVelocity;
}

Vector3 PhysicsObject::DragForce()
{
	// Check if the value is more than 0, do not want to divide by 0
	if (m_Velocity == 0) { return Vector3(0, 0, 0); }

	// Calculate drag using the fluid density, velocity squared, drag coefficient and cross sectional area
	float DensityOfFluid = 1.225; // Density of Air 
	float Drag = Vector::Magnitude((DensityOfFluid * Vector::Pow(m_Velocity, 2) * m_DragCoef * 1) * 0.5);

	// Intergration
	Vector3 CopyVelocity = m_Velocity * -1;
	CopyVelocity = Vector::Normalise(CopyVelocity) * Drag;
	return CopyVelocity;
}

Vector3 PhysicsObject::GravityForce()
{
	// Calculate the Distance from Object to Ground (0, 0, 0 will always be the ground)
	float t_Distance = Vector::Magnitude((m_Transform->GetPosition().x - 0));

	// Use Gravity Formula as Reference to mass of Object and Equation (10 reference to the "mass" of the ground, which 10 is a good angle for)
	Vector3 t_Gravity = (GetGravity() * m_Mass * GetGravity()) / std::pow(t_Distance, 2);

	// Inverse the Gravity
	t_Gravity *= -1;

	return t_Gravity;
}

float PhysicsObject::GetDensity()
{
	float Volume = m_Transform->GetScale().x * m_Transform->GetScale().y * m_Transform->GetScale().z;
	return m_Mass / Volume;
}
