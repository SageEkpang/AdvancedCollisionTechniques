#include "MassPointSpring.h"

MassPointSpring::MassPointSpring(Particle* other, double springConstant, double restLength)
	: m_Other(other), m_SpringConstant(springConstant), m_RestLength(restLength)
{
	
}

MassPointSpring::~MassPointSpring()
{



}

void MassPointSpring::UpdateForce(Particle* particle, float deltaTime)
{
	// Vector of the Spring
	//Vector3 t_Force;
	//particle->GetTransform()->GetPosition(); // TODO: Change to measure the vector of the spring
	//t_Force -= m_Other->GetTransform()->GetPosition();

	//// Magnitude of the Force
	//float t_Magnitude = Vector::Magnitude(t_Force);
	//t_Magnitude = fabsf(t_Magnitude - m_RestLength);
	//t_Magnitude *= m_SpringConstant;

	//// Calculate the Final Force and Apply it
	//Vector3 t_ForceNorm = Vector::Normalise(t_Force);
	//t_ForceNorm *= -t_Magnitude;
	//particle->AddForce(t_ForceNorm);
}
