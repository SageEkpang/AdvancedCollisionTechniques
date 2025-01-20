#include "MassAggregate.h"

MassAggregate::MassAggregate(std::vector<Vector3> points)
{


}

MassAggregate::~MassAggregate()
{



}

void MassAggregate::BuildMassAggregateSystem()
{






}

void MassAggregate::SimulatePhysicsPoints(float deltaTime)
{
	for (int i = 0; i < m_MassPoints.size(); ++i)
	{
		// Update Mass Points
		m_MassPoints[i].Update(deltaTime);
	}
}
