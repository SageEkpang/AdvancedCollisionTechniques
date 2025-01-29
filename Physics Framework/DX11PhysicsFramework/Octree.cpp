#include "Octree.h"

Octant* Octree::BuildOctree(Vector3 centre, float halfWidth, int stopDepth)
{


	return nullptr;
}

Octree::Octree(Vector3 centre, float halfWidth, int stopDepth)
{

}

Octree::~Octree()
{
	// Clear the Octant on the Destructor 
	ClearOctant();
}

void Octree::InsertEntity(PhysicsObject* physicsEntity)
{


}

void Octree::InsertEntities(std::vector<PhysicsObject*> physicsEntities)
{


}

void Octree::QueryTree()
{




}

void Octree::QueryTree(Octant* octantTree)
{



}

void Octree::ClearOctant(int index)
{




}

void Octree::ClearOctant()
{

	std::list<Vector3>::iterator itr;

	// Check if Octant Exists
	if (m_Octant)
	{
		// Check if there are any children created in the Octant
		if (m_Octant->child)
		{


		}
		else
		{
			// If there are no Children then clear the Octant
			m_Octant->objList.clear();
		}
	}


}
