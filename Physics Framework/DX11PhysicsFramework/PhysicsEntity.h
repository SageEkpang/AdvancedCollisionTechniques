#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "ComponentEntity.h"
#include "Transform.h"

// GRAVITY DEFINE(s)
#define GRAVITY_EARTH 9.81f
#define GRAVITY_MARS 3.7f
#define GRAVITY_SATURN 10.5f
#define GRAVITY_SUN 293.0f
#define GRAVITY_MERCURY 3.7f
#define GRAVITY_URANUS 9.0f

// PHYSICS BODY
class PhysicsEntity : public ComponentEntity
{
public:

	// Physics Variables
	Vector3 m_Velocity = VECTOR3_ZERO;
	Vector3 m_Acceleration = VECTOR3_ZERO;
	Vector3 m_NetForce = VECTOR3_ZERO;

	// Mass Variables
	mutable float m_Gravity = GRAVITY_EARTH;
	float m_Mass = 1.0f;
	float m_Weight = 0.0f;

	// Force Variables
	float m_Drag = 1.0f;
	float m_DragCoef = 1.0f;
	float m_Friction = 1.0f;
	float m_FrictionCoef = 0.0f;

	// Collision Variables
	bool m_HasCollided = false;

	// Simulation Variables
	bool m_SimulateGravity = true;
	bool m_SimulateFriction = false;
	bool m_SimulateDrag = false;


public:

	// CLASS FUNCTION(s)
	PhysicsEntity();
	virtual ~PhysicsEntity();


	// ADDITIONAL FUNCTION(s)

	/// <summary> Add forces that effect an object to the total Net force </summary>
	void AddForce(Vector3 force) { m_NetForce += force; }

	/// <summary>  Calculate the acceleration force of the object </summary>
	void CalculateAcceleration(float deltaTime);


	// PHYSICS FORMULA FUNCTION(s)

	/// <summary> Add Friction force that effects an objects movement on the ground or a surface </summary>
	Vector3 FrictionForce();

	/// <summary> Add Drag force that effects the objects movement with wind and a counter force to the game object </summary>
	Vector3 DragForce(); // NOTE: Air Resistance

	/// <summary> Add Gravity force that effects the objects downwards force </summary>
	Vector3 GravityForce();

	/// <summary> Add Tension force that effects the object spring / rope calculation </summary>
	Vector3 TensionForce();

	inline void ApplyForce(Vector3 force) { m_NetForce += force; }
	inline void ApplyForce(float x_force, float y_force, float z_force) { m_NetForce += Vector3(x_force, y_force, z_force); }

	inline void ApplyForceX(float x_force) { m_NetForce.x += x_force; }
	inline void ApplyForceY(float y_force) { m_NetForce.y += y_force; }
	inline void ApplyForceZ(float z_force) { m_NetForce.z += z_force; }

	inline void ApplyImpulse(Vector3 impulse) { m_Velocity += impulse; }
	inline void ApplyImpulse(float x, float y, float z) { m_Velocity += Vector3(x, y, z); }

	inline void ApplyImpulseX(float x_impulse) { m_Velocity.x += x_impulse; }
	inline void ApplyImpulseY(float y_impulse) { m_Velocity.y += y_impulse; }
	inline void ApplyImpulseZ(float z_impulse) { m_Velocity.z += z_impulse; }

	/// <summary> Add Relative force that effects the objects movement </summary>
	// virtual void AddRelativeForce(Vector3 force, Vector3 point) { };


	// BASE FUNCTION(s)

	/// <summary> Default Update Function for Class </summary>
	virtual void Update(float deltaTime) override;
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device) override;

	// GETTER FUNCTION(s)
	Vector3 GetVelocity() { return m_Velocity; }
	Vector3 GetAcceleration() { return m_Acceleration; }
	Vector3 GetGravity() { return Vector3(0.0f, m_Gravity, 0.0f); }
	Vector3 GetNetForce() { return m_NetForce; }

	inline float GetMass() { return m_Mass; }
	inline float GetInverseMass() { if (m_Mass == 0) return 0; return 1 / m_Mass; }

	inline float GetWeight() { return m_Mass * m_Gravity; }
	float GetDensity();

	// SETTER FUNCTION(s)
	virtual inline void SetVelocity(Vector3 velocity) { m_Velocity = velocity; }
	inline void SetVelocity(float x, float y, float z) { m_Velocity = Vector3(x, y, z); }

	inline void SetAcceleration(Vector3 acceleration) { m_Acceleration = acceleration; }
	inline void SetAcceleration(float x, float y, float z) { m_Acceleration = Vector3(x, y, z); }

};

#endif