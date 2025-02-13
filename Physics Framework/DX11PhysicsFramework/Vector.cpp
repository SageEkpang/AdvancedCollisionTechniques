#include "Vector.h"
#include "BoxCollider.h"
#include "OBBCollider.h"

Vector3 Vector::Inverse(Vector3 Value)
{
	return Vector3(-1 * Value.x, -1 * Value.y, -1 * Value.z);
}

Vector3 Vector::Reverse(Vector3 Value)
{
	float VecX = -Value.x;
	float VecY = -Value.y;
	float VecZ = -Value.z;
	return Vector3(VecX, VecY, VecZ);
}

Vector3 Vector::CalculateVelocity(Vector3 Value, float DeltaTime)
{
	float VecX = (Value.x / DeltaTime);
	float VecY = (Value.y / DeltaTime);
	float VecZ = (Value.z / DeltaTime);

	return Vector3(VecX, VecY, VecZ);
}

Vector3 Vector::CalculateVelocity(float ValueX, float ValueY, float ValueZ, float DeltaTime)
{
	float VecX = (ValueX / DeltaTime);
	float VecY = (ValueY / DeltaTime);
	float VecZ = (ValueZ / DeltaTime);

	return Vector3(VecX, VecY, VecZ);
}

Vector3 Vector::Pow(Vector3 value, float power)
{
	return Vector3(std::pow(value.x, power), std::pow(value.y, power), std::pow(value.z, power));
}

Vector3 Vector::XMFLOAT3toVector3(XMFLOAT3 value)
{
	Vector3 temp;
	temp.x = value.x;
	temp.y = value.y;
	temp.z = value.z;

	return Vector3(temp);
}

float Vector::CalculateDotProduct(Vector3 Value1, Vector3 Value2) // Dot Product
{
	Vector3 NormVec1 = Normalise(Value1);
	Vector3 NormVec2 = Normalise(Value2);
	return (NormVec1.x * NormVec2.x) + (NormVec1.y * NormVec2.y) + (NormVec1.z * NormVec2.z);
}

float Vector::CalculateDotProductNotNorm(Vector3 value1, Vector3 value2)
{
	return (value1.x * value2.x) + (value1.y * value2.y) + (value1.z * value2.z);
}

float Vector::CalculateDotProduct(float Value1X, float Value1Y, float Value1Z, float Value2X, float Value2Y, float Value2Z) // Dot Product
{
	Vector3 NormVec1 = Normalise(Vector3(Value1X, Value1Y, Value1Z));
	Vector3 NormVec2 = Normalise(Vector3(Value2X, Value2Y, Value2Z));
	return (NormVec1.x * NormVec2.x) + (NormVec1.y * NormVec2.y) + (NormVec1.z * NormVec2.z);
}

Vector3 Vector::CalculateCrossProductV(Vector3 Value1, Vector3 Value2)
{
	float TempX = (Value1.y * Value2.z - Value1.z * Value2.y);
	float TempY = (Value1.z * Value2.x - Value1.x * Value2.z);
	float TempZ = (Value1.x * Value2.y - Value1.y * Value2.x);

	return Vector3(TempX, TempY, TempZ);
}

float Vector::CalculateCrossProduct(Vector3 Value1, Vector3 Value2)
{
	float CrossProduct =
		(Value1.y * Value2.z - Value1.z * Value2.y) +
		(Value1.z * Value2.x - Value1.x * Value2.z) +
		(Value1.x * Value2.y - Value1.y * Value2.x);

	return CrossProduct;
}

Vector3 Vector::CalculateCrossProduct(float Value1X, float Value1Y, float Value1Z, float Value2X, float Value2Y, float Value2Z)
{
	float TempX = (Value1Y * Value2Z - Value1Z * Value2Y);
	float TempY = (Value1Z * Value2X - Value1X * Value2Z);
	float TempZ = (Value1X * Value2Y - Value1Y * Value2X);

	return Vector3(TempX, TempY, TempZ);
}

float Vector::MagnitudeNoSqrt(Vector3 Value)
{
	return (Value.x * Value.x) + (Value.y * Value.y) + (Value.z * Value.z);
}

float Vector::Magnitude(Vector3 Value)
{
	return sqrt((Value.x * Value.x) + (Value.y * Value.y) + (Value.z * Value.z));
}

float Vector::Magnitude(float ValueX, float ValueY, float ValueZ)
{
	return sqrt((ValueX * ValueX) + (ValueY * ValueY) + (ValueZ * ValueZ));
}

Vector3 Vector::Normalise(Vector3 Value)
{
	float Length = Magnitude(Value);
	if (Length == 0)
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	float NormX = Value.x / Length;
	float NormY = Value.y / Length;
	float NormZ = Value.z / Length;

	return Vector3(NormX, NormY, NormZ);
}

Vector3 Vector::Normalise(float ValueX, float ValueY, float ValueZ)
{
	float Length = Magnitude(Vector3(ValueX, ValueY, ValueZ));

	float NormX = ValueX / Length;
	float NormY = ValueY / Length;
	float NormZ = ValueZ / Length;

	return Vector3(NormX, NormY, NormZ);
}

Vector3 Vector::DistanceTo(Vector3 Value1, Vector3 Value2)
{
	return Vector3(Value2 - Value1);
}

Interval Vector::GetInterval(BoxCollider* box, Vector3* axis)
{
	Vector3 t_Min = box->GetMin();
	Vector3 t_Max = box->GetMax();

	Vector3 t_Vertex[8] = {
		Vector3(t_Min.x, t_Max.y, t_Max.z),
		Vector3(t_Min.x, t_Max.y, t_Min.z),
		Vector3(t_Min.x, t_Min.y, t_Max.z),
		Vector3(t_Min.x, t_Min.y, t_Min.z),

		Vector3(t_Max.x, t_Max.y, t_Max.z),
		Vector3(t_Max.x, t_Max.y, t_Min.z),
		Vector3(t_Max.x, t_Min.y, t_Max.z),
		Vector3(t_Max.x, t_Min.y, t_Min.z)
	};

	Interval t_Result;
	t_Result.min = t_Result.max = Vector::CalculateDotProduct(axis[0], t_Vertex[0]);

	for (int i = 1; i < 8; ++i)
	{
		float t_Projection = Vector::CalculateDotProduct(axis[i], t_Vertex[i]);
		t_Result.min = (t_Projection < t_Result.min) ? t_Projection : t_Result.min;
		t_Result.max = (t_Projection > t_Result.max) ? t_Projection : t_Result.max;
	}

	return t_Result;
}

Interval Vector::GetInterval(OBBCollider& OBBBox, Vector3& axis)
{
	Vector3 t_Vertex[8];
	Vector3 t_Position = OBBBox.GetPosition();
	Vector3 t_Size = OBBBox.GetScale();

	const float* t_Orientation = OBBBox.GetOrientationArray();

	Vector3 t_Axis[] = {
		Vector3(t_Orientation[0], t_Orientation[1], t_Orientation[2]),
		Vector3(t_Orientation[3], t_Orientation[4], t_Orientation[5]),
		Vector3(t_Orientation[6], t_Orientation[7], t_Orientation[8])
	};

	t_Vertex[0] = t_Position + t_Axis[0] * t_Size.x + t_Axis[1] * t_Size.y + t_Axis[2] * t_Size.z;
	t_Vertex[1] = t_Position - t_Axis[0] * t_Size.x + t_Axis[1] * t_Size.y + t_Axis[2] * t_Size.z;
	t_Vertex[2] = t_Position + t_Axis[0] * t_Size.x - t_Axis[1] * t_Size.y + t_Axis[2] * t_Size.z;
	t_Vertex[3] = t_Position + t_Axis[0] * t_Size.x + t_Axis[1] * t_Size.y - t_Axis[2] * t_Size.z;
	t_Vertex[4] = t_Position - t_Axis[0] * t_Size.x - t_Axis[1] * t_Size.y - t_Axis[2] * t_Size.z;
	t_Vertex[5] = t_Position + t_Axis[0] * t_Size.x - t_Axis[1] * t_Size.y - t_Axis[2] * t_Size.z;
	t_Vertex[6] = t_Position - t_Axis[0] * t_Size.x + t_Axis[1] * t_Size.y - t_Axis[2] * t_Size.z;
	t_Vertex[7] = t_Position - t_Axis[0] * t_Size.x - t_Axis[1] * t_Size.y + t_Axis[2] * t_Size.z;

	Interval t_Result;
	t_Result.min = t_Result.max = Vector::CalculateDotProduct(axis, t_Vertex[0]);

	for (int i = 1; i < 8; ++i)
	{
		float t_Projection = Vector::CalculateDotProduct(axis, t_Vertex[i]);
		t_Result.min = (t_Projection < t_Result.min) ? t_Projection : t_Result.min;
		t_Result.max = (t_Projection > t_Result.max) ? t_Projection : t_Result.max;
	}

	return t_Result;
}

bool Vector::OverlapOnAxis(BoxCollider* box, OBBCollider* OBBBox, Vector3* axis)
{
	Interval t_Box = GetInterval(box, axis);
	// Interval t_OBBBox = GetInterval(OBBBox, axis);
	/// return ((t_OBBBox.min <= t_Box.max) && (t_Box.min <= t_OBBBox.max));
	return false;
}

double Vector::PolygonArea(double x[], double y[], int number)
{
	double t_Area = 0.0;

	int t_J = number - 1;

	for (int i = 0; i < number; ++i)
	{
		t_Area += (x[t_J] + x[t_J]) * (y[t_J] - y[t_J]);
		t_J = i;
	}

	return std::abs(t_Area / 2.0);
}
