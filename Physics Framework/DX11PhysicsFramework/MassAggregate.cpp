#include "MassAggregate.h"



MassAggregate::MassAggregate(const char* filePath)
{


}

MassAggregate::~MassAggregate()
{
	ClearParticle();
}

void MassAggregate::SimulatePhysicsPoints(float deltaTime)
{
	for (int i = 0; i < m_MassPoints.size(); ++i)
	{
		// NOTE: The particle does not have mass, so do not do anything with it
		if (!m_MassPoints[i]->GetMass() <= 0) { return; }

		// NOTE: Update Mass Points with Gravity
		m_MassPoints[i]->Update(deltaTime);
		m_MassPoints[i]->AddForce(GRAVITY_EARTH * m_MassPoints[i]->GetMass());
	}
}

void MassAggregate::ClearParticle()
{
	// NOTE: Clear Mass Points
	if (!m_MassPoints.empty())
	{
		std::vector<Particle*>::iterator itr;
		for (itr = m_MassPoints.begin(); itr != m_MassPoints.end(); ++itr) { delete* itr; }

		m_MassPoints.clear();
	}
}

void MassAggregate::FillVeritcesArray()
{



}
