#include "Octree.h"

Octree::Octree(Vector3 centre, float halfWidth, int stopDepth)
{
	m_Octant = new Octant();
	m_Octant = BuildOctree(centre, halfWidth, stopDepth);
}

Octree::~Octree()
{
	delete m_Octant;
}

Octant* Octree::BuildOctree(Vector3 centre, float halfWidth, int stopDepth)
{
	if (stopDepth < 0)
	{
		return nullptr;
	}
	else
	{
		// Construct and fill in the root of this subtree (Root refers to the arbitary starting value for the tree)
		Octant* t_Octant = new Octant();
		t_Octant->centre = centre;
		t_Octant->halfWidth = halfWidth;
		t_Octant->objList.clear();

		// Recursively construct the eight children of the Subtree
		Vector3 t_Offset = Vector3();
		float t_Step = halfWidth * 0.5f;

		for (int i = 0; i < 8; ++i)
		{
			t_Offset.x = ((i & 1) ? t_Step : -t_Step);
			t_Offset.y = ((i & 2) ? t_Step : -t_Step);
			t_Offset.z = ((i & 4) ? t_Step : -t_Step);
			t_Octant->child[i] = BuildOctree(centre + t_Offset, t_Step, stopDepth - 1);
		}

		return t_Octant;
	}
}

void Octree::P_InsertEntity(Octant* tree, GameObjectEntity* entity)
{
	int t_Index = 0;
	bool t_Straddle = false;
	// Compute the Octant Index using the Object Sphere Radius
	// If straddling any of the dividing x, y, z planes, exit directly

	for (int i = 0; i < 3; ++i)
	{
		float t_Delta = 0;
		if (i == 0) { t_Delta = entity->m_Transform.m_Position.x - tree->centre.x; }
		if (i == 1) { t_Delta = entity->m_Transform.m_Position.y - tree->centre.y; }
		if (i == 2) { t_Delta = entity->m_Transform.m_Position.z - tree->centre.z; }

		if (std::abs(t_Delta) <= 1) // CHOICE: Can raise to the power of 2 to make it more accurate
		{
			t_Straddle = true;
			break;
		}

		// ZYX
		if (t_Delta > 0.0f) { t_Index |= (1 << i); }
	}

	// Insert into child subtree if it exists already
	if (t_Straddle == false && tree->child[t_Index])
	{
		P_InsertEntity(tree->child[t_Index], entity);
	}
	else
	{
		// Straddling, or no child octant to descend into, so link object into linked list at this node
		tree->objList.push_back(entity);
	}

}

void Octree::P_UpdateTree(Octant* tree, const float deltaTime)
{
	for (auto& v : tree->objList)
	{
		v->Update(deltaTime);
	}

	for (int i = 0; i < 8; ++i)
	{
		if (tree->child[i])
		{
			for (auto& v : tree->child[i]->objList) { v->Update(deltaTime); }
		}
	}

	for (int i = 0; i < 8; ++i)
	{
		if (tree->child[i]) { P_UpdateTree(tree->child[i], deltaTime); }
	}
}

void Octree::P_QueryTree(Octant* tree, CollisionManifold(*CollisionFunc)(GameObjectEntity*, GameObjectEntity*), void(*ResolveFunc)(GameObjectEntity*, GameObjectEntity*, float, Vector3))
{
	// Keep track of all ancester objects lists in a stack
	std::list<GameObjectEntity*> t_AncesterStackList;
	t_AncesterStackList.clear();
	t_AncesterStackList = tree->objList;

	std::list<GameObjectEntity*>::iterator t_ObjectA, t_ObjectB;

	// Collision Response Calculations
	for (t_ObjectA = t_AncesterStackList.begin(); t_ObjectA != t_AncesterStackList.end(); ++t_ObjectA)
	{
		for (t_ObjectB = tree->objList.begin(); t_ObjectB != tree->objList.end(); ++t_ObjectB)
		{
			// If they are the same, skip iteration
			if (*t_ObjectA == *t_ObjectB) break;

			CollisionManifold t_CollisionManifold = CollisionManifold();



		}
	}

	// recursively visit children
	for (int i = 0; i < 8; ++i)
	{
		if (tree->child[i])
		{
			P_QueryTree(tree->child[i], CollisionFunc, ResolveFunc);
		}
	}
}

void Octree::P_ClearOctant(Octant* tree, int index)
{
	if (tree == nullptr) { return; }

	if (!tree->objList.empty() && tree != nullptr) { tree->objList.clear(); }

	for (int i = 0; i < 8; ++i)
	{
		P_ClearOctant(tree->child[index], i);
	}

	if (tree->child[index] != nullptr)
	{
		tree->objList.clear();
		tree->child[index]->objList.clear();
	}
}

void Octree::InsertEntity(GameObjectEntity* entity)
{
	int t_Index = 0;
	bool t_Straddle = false;
	// Compute the Octant Index using the Object Sphere Radius
	// If straddling any of the dividing x, y, z planes, exit directly

	for (int i = 0; i < 3; ++i)
	{
		float t_Delta = 0;
		if (i == 0) { t_Delta = entity->m_Transform.m_Position.x - m_Octant->centre.x; }
		if (i == 1) { t_Delta = entity->m_Transform.m_Position.y - m_Octant->centre.y; }
		if (i == 2) { t_Delta = entity->m_Transform.m_Position.z - m_Octant->centre.z; }

		if (std::abs(t_Delta) <= 1) // CHOICE: Can raise to the power of 2 to make it more accurate
		{
			t_Straddle = true;
			break;
		}

		// ZYX
		if (t_Delta > 0.0f) { t_Index |= (1 << i); }
	}

	// Insert into child subtree if it exists already
	if (t_Straddle == false && m_Octant->child[t_Index])
	{
		P_InsertEntity(m_Octant->child[t_Index], entity);
	}
	else
	{
		// Straddling, or no child octant to descend into, so link object into linked list at this node
		m_Octant->objList.push_back(entity);
	}
}

void Octree::UpdateTree(const float deltaTime)
{
	for (auto& v : m_Octant->objList)
	{
		v->Update(deltaTime);
	}

	for (int i = 0; i < 8; ++i)
	{
		if (m_Octant->child[i])
		{
			for (auto& v : m_Octant->child[i]->objList) { v->Update(deltaTime); }
		}
	}

	for (int i = 0; i < 8; ++i)
	{
		if (m_Octant->child[i]) 
		{ 
			P_UpdateTree(m_Octant->child[i], deltaTime); 
		}
	}
}

void Octree::QueryTree(CollisionManifold(*CollisionFunc)(GameObjectEntity*, GameObjectEntity*), void(*ResolveFunc)(GameObjectEntity*, GameObjectEntity*, float, Vector3))
{
	// Keep track of all ancester objects lists in a stack
	std::list<GameObjectEntity*> t_AncesterStackList;
	t_AncesterStackList.clear();
	t_AncesterStackList = m_Octant->objList;

	std::list<GameObjectEntity*>::iterator t_ObjectA, t_ObjectB;

	// Collision Response Calculations
	for (t_ObjectA = t_AncesterStackList.begin(); t_ObjectA != t_AncesterStackList.end(); ++t_ObjectA)
	{
		for (t_ObjectB = m_Octant->objList.begin(); t_ObjectB != m_Octant->objList.end(); ++t_ObjectB)
		{
			// If they are the same, skip iteration
			if (*t_ObjectA == *t_ObjectB) break;

			// NOTE: Use a function pointer to allow for any collision function to pass in
			CollisionManifold t_CollisionManifold = CollisionManifold();
			t_CollisionManifold = CollisionFunc(*t_ObjectA, *t_ObjectB);

			// NOTE: If the collision is true, resolve it
			if (t_CollisionManifold.hasCollision == true)
			{
				// NOTE: Work out the Material Co-efficient
				double t_RestCoef = 1.0;

				// NOTE: Resolve Collision Function Pointer
				ResolveFunc(*t_ObjectA, *t_ObjectB, static_cast<float>(t_RestCoef), t_CollisionManifold.collisionNormal);
			}
		}
	}

	// NOTE: Recursively Call the Next Function
	for (int i = 0; i < 8; ++i)
	{
		if (m_Octant->child[i])
		{
			P_QueryTree(m_Octant->child[i], CollisionFunc, ResolveFunc);
		}
	}
}

void Octree::ClearTree(int index)
{
	if (m_Octant == nullptr) { return; }

	if (!m_Octant->objList.empty() && m_Octant != nullptr) { m_Octant->objList.clear(); }

	for (int i = 0; i < 8; ++i)
	{
		P_ClearOctant(m_Octant->child[index], i);
	}

	if (m_Octant->child[index] != nullptr)
	{
		m_Octant->objList.clear();
		m_Octant->child[index]->objList.clear();
	}
}
