#ifndef MATERIAL_RESTITUTION_H
#define MATERAIL_RESTITUTION_H

// ABSTRACT CLASS

// NEEDED INCLUDE(s)
#include "Constants.h"
// #include "Structures.h"
#include <map>
#include <utility>


enum class MaterialTypes : std::int8_t
{
	MATERIAL_SILICON,
	MATERIAL_ALUMINA,
	MATERIAL_STAINLESS_STEEL,
	MATERIAL_TUNGSTEN,
	MATERIAL_ALUMINUM,
	MATERIAL_COPPER,
	MATERIAL_NICKEL,
	MATERIAL_ZINC
};

enum class DragShapeTypes : std::int8_t
{
	DRAG_SPHERE,
	DRAG_HALF_SPHERE,
	DRAG_CONE,
	DRAG_CUBE,
	DRAG_ANGLED_CUBE,
	DRAG_LONG_CYLINDER,
	DRAG_SHORT_CYLINDER,
	DRAG_STREAMLINED_BODY,
	DRAG_STREAMLINED_HALF_BODY
};

// Make life easier
typedef std::pair<MaterialTypes, MaterialTypes> Mat2;

class MaterialCoefficient
{
private:

	// MATERIAL RESTIUTION Coef
	std::map<Mat2, double> m_MaterialRestitution;
	std::map<Mat2, double> m_MaterialFriction;
	std::map<DragShapeTypes, double> m_ShapeDrag;

public:

	// CLASS FUNCTION(s)
	MaterialCoefficient();
	~MaterialCoefficient();


	// BASE FUNCTION(s)
	/// <summary> Return Coef of Restitution of the material at that index </summary>
	double MaterialRestCoef(MaterialTypes materialA, MaterialTypes materialB);
	double MaterialFricCoef(MaterialTypes materialA, MaterialTypes materialB);
	double ShapeDragCoef(DragShapeTypes shapeA);

};

#endif