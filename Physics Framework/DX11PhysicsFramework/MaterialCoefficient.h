#ifndef MATERIAL_RESTITUTION_H
#define MATERAIL_RESTITUTION_H

// ABSTRACT CLASS

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structures.h"

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