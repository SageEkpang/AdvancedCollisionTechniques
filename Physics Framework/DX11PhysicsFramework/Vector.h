#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include "Structures.h"

class BoxCollider;
class OBBCollider;

class Vector
{
private:
public:

	// CLASS FUNCTION(s)

	Vector() { };
	~Vector() { };

	// BASE FUNCTION(s)

	// Basic Maths
	static Vector3 Inverse(Vector3 Value);
	static Vector3 Reverse(Vector3 Value);

	static Vector3 CalculateVelocity(Vector3 Value, float DeltaTime); // This
	static Vector3 CalculateVelocity(float ValueX, float ValueY, float ValueZ, float DeltaTime); // This

	static Vector3 Pow(Vector3 Value, float power);

	static Vector3 XMFLOAT3toVector3(XMFLOAT3 value);

	// Vector Maths
	static float CalculateDotProduct(Vector3 Value1, Vector3 Value2);
	static float CalculateDotProductNotNorm(Vector3 value1, Vector3 value2);
	static float CalculateDotProduct(float Value1X, float Value1Y, float Value1Z, float Value2X, float Value2Y, float Value2Z);

	static Vector3 CalculateCrossProductV(Vector3 Value1, Vector3 Value2);
	static Vector3 CalculateCrossProduct(float Value1X, float Value1Y, float Value1Z, float Value2X, float Value2Y, float Value2Z);
	static float CalculateCrossProduct(Vector3 Value1, Vector3 Value2);

	static float MagnitudeNoSqrt(Vector3 Value);
	static float Magnitude(Vector3 Value); // May need to convert this back to non-static later on
	static float Magnitude(float ValueX, float ValueY, float ValueZ);

	static Vector3 Normalise(Vector3 Value);
	static Vector3 Normalise(float ValueX, float ValueY, float ValueZ);

	static Vector3 DistanceTo(Vector3 Value1, Vector3 Value2);

	// SAT Testing
	static Interval GetInterval(BoxCollider* box, Vector3* axis);
	static Interval GetInterval(OBBCollider* OBBBox, Vector3* axis);

	static bool OverlapOnAxis(BoxCollider* box, OBBCollider* OBBBox, Vector3* axis);

	static double PolygonArea(double x[], double y[], int number);



};

#endif

