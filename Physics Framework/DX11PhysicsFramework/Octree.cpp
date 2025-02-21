#include "Octree.h"

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

Octree::Octree()
{
	m_Octant = new Octant();
	m_RegionAmount = 10;
}

Octree::Octree(int regionAmount)
{
	m_Octant = new Octant();
	m_RegionAmount = regionAmount;
}

Octree::Octree(Vector3 centre, float halfWidth, int stopDepth)
{
	m_Octant = new Octant();
	m_Octant = BuildOctree(centre, halfWidth, stopDepth);
}

Octree::~Octree()
{
	// Clear the Octant on the Destructor 
	// ClearOctant(); // FIXME
	delete m_Octant;
}

void Octree::InsertEntity(Octant* tree, PhysicsObject* physicsEntity)
{
	int t_Index = 0;
	bool t_Straddle = false;
	// Compute the Octant Index using the Object Sphere Radius
	// If straddling any of the dividing x, y, z planes, exit directly

	for (int i = 0; i < 3; ++i)
	{
		float t_Delta = 0;
		if (i == 0) { t_Delta = physicsEntity->GetTransform()->GetPosition().x - tree->centre.x; }
		if (i == 1) { t_Delta = physicsEntity->GetTransform()->GetPosition().y - tree->centre.y; }
		if (i == 2) { t_Delta = physicsEntity->GetTransform()->GetPosition().z - tree->centre.z; }

		if (std::abs(t_Delta) <= physicsEntity->GetRadius()) // CHOICE: Can raise to the power of 2 to make it more accurate
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
		InsertEntity(tree->child[t_Index], physicsEntity);
	}
	else
	{
		// Straddling, or no child octant to descend into, so link object into linked list at this node
		tree->objList.push_back(physicsEntity);
	}

}

void Octree::InsertEntities(Octant* tree, std::vector<PhysicsObject*> physicsEntities)
{
	std::list<PhysicsObject*> t_EntityList;
	t_EntityList.clear();

	if (physicsEntities.empty()) { std::cout << "List is Empty" << std::endl; }
	t_EntityList.insert(t_EntityList.end(), physicsEntities.begin(), physicsEntities.end());

	// Compute the Octant Index using the Object Sphere Radius
	// If straddling any of the dividing x, y, z planes, exit directly

	for (auto& entity : t_EntityList)
	{
		int t_Index = 0, t_Straddle = 0;

		for (int i = 0; i < 3; ++i)
		{
			float t_Delta = 0;
			if (i == 0) { t_Delta = entity->GetTransform()->GetPosition().x - tree->centre.x; }
			if (i == 1) { t_Delta = entity->GetTransform()->GetPosition().y - tree->centre.y; }
			if (i == 2) { t_Delta = entity->GetTransform()->GetPosition().z - tree->centre.z; }

			if (std::abs(t_Delta) <= entity->GetRadius()) // CHOICE: Can raise to the power of 2 to make it more accurate
			{
				t_Straddle = 1;
				break;
			}

			// ZYX
			if (t_Delta > 0.0f) { t_Index |= (1 << i); }
		}

		// Insert into child subtree if it exists already
		if (!t_Straddle && tree->child[t_Index])
		{
			InsertEntities(tree->child[t_Index], physicsEntities);
		}
		else
		{
			// Straddling, or no child octant to descend into, so link object into linked list at this node
			tree->objList.push_back(entity);
		}
	}

}

void Octree::UpdateTree(Octant* tree, const float deltaTime)
{
	for (auto& v : tree->objList)
	{
		// v->UpdateQuery(deltaTime);
	}

	for (int i = 0; i < 8; ++i)
	{
		if (tree->child[i])
		{
			// for (auto& v : tree->child[i]->objList) { v->updateQuery(deltaTime); }
		}
	}

	for (int i = 0; i < 8; ++i)
	{
		if (tree->child[i]) { UpdateTree(tree->child[i], deltaTime); }
	}
}

void Octree::QueryTree()
{
	// Keep track of all ancester objects lists in a stack
	std::list<PhysicsObject*> t_AncesterStackList;
	t_AncesterStackList.clear();
	t_AncesterStackList = m_Octant->objList;

	std::list<PhysicsObject*>::iterator t_ObjectA;
	std::list<PhysicsObject*>::iterator t_ObjectB;

	// Collision Response Calculations
	for (t_ObjectA = t_AncesterStackList.begin(); t_ObjectA != t_AncesterStackList.end(); ++t_ObjectA)
	{
		for (t_ObjectB = m_Octant->objList.begin(); t_ObjectB != m_Octant->objList.end(); ++t_ObjectB)
		{
			// If they are the same, skip iteration
			if (*t_ObjectA == *t_ObjectB) break;

			// Collision Test
			// if (CheckCollision(*t_ObjectA, *t_ObjectB)) { ResolveCollision(*t_ObjectA, *t_ObjectB); }
		}
	}

	// Recursively visit Children
	for (int i = 0; i < 8; ++i)
	{
		if (m_Octant->child[i])
		{
			QueryTree(m_Octant->child[i]);
		}
	}
}

void Octree::QueryTree(Octant* tree)
{
	// Keep track of all ancester objects lists in a stack
	std::list<PhysicsObject*> t_AncesterStackList;
	t_AncesterStackList.clear();
	t_AncesterStackList = tree->objList;

	std::list<PhysicsObject*>::iterator t_ObjectA, t_ObjectB;

	// Collision Response Calculations
	for (t_ObjectA = t_AncesterStackList.begin(); t_ObjectA != t_AncesterStackList.end(); ++t_ObjectA)
	{
		for (t_ObjectB = tree->objList.begin(); t_ObjectB != tree->objList.end(); ++t_ObjectB)
		{
			// If they are the same, skip iteration
			if (*t_ObjectA == *t_ObjectB) break;

			// Collision Test
			// if (CheckCollision(*t_ObjectA, *t_ObjectB)) { ResolveCollision(*t_ObjectA, *t_ObjectB); }
		}
	}

	// recursively visit children
	for (int i = 0; i < 8; ++i)
	{
		if (tree->child[i])
		{
			QueryTree(tree->child[i]);
		}
	}


}

void Octree::ClearOctant(int index)
{
	if (m_Octant == nullptr) { return; }

	if (!m_Octant->objList.empty() && m_Octant != nullptr) { m_Octant->objList.clear(); }

	for (int i = 0; i < 8; ++i)
	{
		ClearOctant(m_Octant->child[index], i);
	}

	if (m_Octant->child[index] != nullptr)
	{
		m_Octant->objList.clear();
		m_Octant->child[index]->objList.clear();
	}
}

void Octree::ClearOctant(Octant* tree, int index)
{
	if (tree == nullptr) { return; }

	if (!tree->objList.empty() && tree != nullptr) { tree->objList.clear(); }

	for (int i = 0; i < 8; ++i)
	{
		ClearOctant(tree->child[index], i);
	}

	if (tree->child[index] != nullptr)
	{
		tree->objList.clear();
		tree->child[index]->objList.clear();
	}
}