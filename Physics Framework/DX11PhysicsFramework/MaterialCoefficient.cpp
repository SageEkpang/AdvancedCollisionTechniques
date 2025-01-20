#include "MaterialCoefficient.h"

// Useful link for Material Coef Restiution
// https://www.rocscience.com/help/rocfall/documentation/slope/materials/reference-tables/rocscience-coefficient-of-restitution-table-in-rocfall

MaterialCoefficient::MaterialCoefficient()
{
	// 
	t_MaterialPair.first = MATERIAL_SILICON;
	t_MaterialPair.second = MATERIAL_ZINC;

	m_MaterialRestitution[t_MaterialPair] = 1.9f; // TODO: Make these in reverse as well due to how the collision will work


	// DRAG COEFFICIENT
	m_ShapeDrag[DRAG_SPHERE] = 0.47f;
	m_ShapeDrag[DRAG_HALF_SPHERE] = 0.42f;
	m_ShapeDrag[DRAG_CONE] = 0.50f;
	m_ShapeDrag[DRAG_CUBE] = 1.05f;
	m_ShapeDrag[DRAG_ANGLED_CUBE] = 0.80f;
	m_ShapeDrag[DRAG_LONG_CYLINDER] = 0.82;
	m_ShapeDrag[DRAG_SHORT_CYLINDER] = 1.15f;
	m_ShapeDrag[DRAG_STREAMLINED_BODY] = 0.04f;
	m_ShapeDrag[DRAG_STREAMLINED_HALF_BODY] = 0.09;
}

MaterialCoefficient::~MaterialCoefficient()
{
	m_MaterialRestitution.clear();
}

double MaterialCoefficient::MaterialRestCoef(MaterialTypes materialA, MaterialTypes materialB)
{
	// Returns the Stored Variable at the Map index of the Material
	Mat2 t_TempPair;
	t_TempPair.first = materialA;
	t_TempPair.second = materialB;

	return m_MaterialRestitution[t_TempPair];
}

double MaterialCoefficient::MaterialFricCoef(MaterialTypes materialA, MaterialTypes materialB)
{
	// Returns the Stored Variable at the Map index of the Material
	Mat2 t_TempPair;
	t_TempPair.first = materialA;
	t_TempPair.second = materialB;

	return m_MaterialFriction[t_TempPair];
}

double MaterialCoefficient::ShapeDragCoef(DragShapeTypes shapeA)
{
	// Returns the Stored Variable at the Map index of the Shape
	return m_ShapeDrag[shapeA];
}
