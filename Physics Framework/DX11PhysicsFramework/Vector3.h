#ifndef VECTOR3_H
#define VECTOR3_H

#include <directxmath.h>
#include <cmath>

typedef struct Vector3
{
	// NOTE: Base Variable(s)
	union { float x, width; };
	union { float y, height; };
	union { float z, length; };

	// Constructor 
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3(const Vector3& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}


	// Operator Overloading

	Vector3 operator+ (Vector3 value)
	{
		return Vector3(x + value.x, y + value.y, z + value.z);
	}

	Vector3 operator+ (float value)
	{
		return Vector3(x + value, y + value, z + value);
	}

	Vector3 operator- (Vector3 value)
	{
		return Vector3(x - value.x, y - value.y, z - value.z);
	}

	Vector3 operator- (float value)
	{
		return Vector3(x - value, y - value, z - value);
	}

	Vector3 operator -()
	{
		this->x *= -1;
		this->y *= -1;
		this->z *= -1;

		return *this;
	}

	Vector3 operator++ ()
	{
		++x;
		++y;
		++z;
		return *this;
	}

	Vector3 operator-- ()
	{
		--x;
		--y;
		--z;
		return *this;
	}

	Vector3 operator* (Vector3 value)
	{
		return Vector3(x * value.x, y * value.y, z * value.z);
	}

	Vector3 operator* (float value)
	{
		return Vector3(x * value, y * value, z * value);
	}

	friend Vector3 operator*(float value, Vector3 rhs)
	{
		return rhs * value;
	}

	Vector3 operator/ (Vector3 value)
	{
		return Vector3(x / value.x, y / value.y, z / value.z);
	}

	Vector3 operator/ (float value)
	{
		return Vector3(x / value, y / value, z / value);
	}

	Vector3 operator+=(Vector3 value)
	{
		this->x += value.x;
		this->y += value.y;
		this->z += value.z;
		return *this;
	}

	Vector3 operator+=(float value)
	{
		this->x += value;
		this->y += value;
		this->z += value;
		return *this;
	}

	Vector3 operator-=(Vector3 value)
	{
		this->x -= value.x;
		this->y -= value.y;
		this->z -= value.z;
		return *this;
	}

	Vector3 operator-=(float value)
	{
		this->x -= value;
		this->y -= value;
		this->z -= value;
		return *this;
	}

	Vector3 operator*=(float value)
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;
		return *this;
	}

	Vector3 operator^(Vector3 value)
	{
		return Vector3(y * value.z - z * value.y,
			-x * value.z + z * value.x,
			x * value.y - y * value.x);
	}

	bool operator==(Vector3 value)
	{
		bool tempX = this->x == value.x ? true : false;
		bool tempY = this->y == value.y ? true : false;
		bool tempZ = this->z == value.z ? true : false;

		if (tempX && tempY && tempZ) return true;

		return false;
	}

	Vector3 operator=(DirectX::XMFLOAT3 value)
	{
		this->x = value.x;
		this->y = value.y;
		this->z = value.z;
		return *this;
	}

	// GREATER THAN / LESS THAN
	bool operator >(Vector3 value)
	{
		bool t_TempX = this->x > value.x ? true : false;
		bool t_TempY = this->y > value.y ? true : false;
		bool t_TempZ = this->z > value.z ? true : false;

		if (t_TempX && t_TempY && t_TempZ) { return true; }

		return false;
	}

	bool operator <(Vector3 value)
	{
		bool t_TempX = this->x < value.x ? true : false;
		bool t_TempY = this->y < value.y ? true : false;
		bool t_TempZ = this->z < value.z ? true : false;

		if (t_TempX && t_TempY && t_TempZ) { return true; }

		return false;
	}




	
	// FUNCTION(s)
	
	DirectX::XMFLOAT3 ToXMFLOAT3()
	{
		return DirectX::XMFLOAT3(this->x, this->y, this->z);
	}

	float LengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	Vector3 Inverse()
	{
		this->x *= -1;
		this->y *= -1;
		this->z *= -1;
	}

	static Vector3 Inverse(Vector3 value)
	{
		value.x *= -1;
		value.y *= -1;
		value.z *= -1;
		return value;
	}

	Vector3 DistanceTo(Vector3 value)
	{
		return Vector3(value - Vector3(x, y, z));
	}

	float* ToArray()
	{
		return &x;
	}

	// MATH FUNCTION(s)
	Vector3 Abs()
	{
		this->x = std::abs(x);
		this->y = std::abs(y);
		this->z = std::abs(z);

		return *this;
	}

	Vector3 fAbs()
	{
		this->x = std::fabs(x);
		this->y = std::fabs(y);
		this->z = std::fabs(z);
		return *this;
	}

	Vector3 Pow(float power) const
	{
		return Vector3(std::powf(this->x, power), std::powf(this->y, power), std::powf(this->z, power));
	}

	float Magnitude() const
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	Vector3 Normalise() const
	{
		float t_Length = this->Magnitude();
		float t_NormX = this->x / t_Length;
		float t_NormY = this->y / t_Length;
		float t_NormZ = this->z / t_Length;

		return Vector3(t_NormX, t_NormY, t_NormZ);
	}

	float Dot(Vector3 value) const
	{
		return (this->x * value.x) + (this->y * value.y) + (this->z * value.z);
	}

	Vector3 Cross(Vector3 value) const
	{
		float t_TempX = (this->y * value.z - this->z * value.y);
		float t_TempY = (this->z * value.x - this->x * value.z);
		float t_TempZ = (this->x * value.y - this->y * value.x);

		return Vector3(t_TempX, t_TempY, t_TempZ);
	}

}Vector3, Vector3D;

#define VECTOR3_ZERO Vector3{0, 0, 0}
#define VECTOR3_ONE Vector3{1, 1, 1}
#define VECTOR3_IDENTITY VECTOR3_ONE

#define VECTOR3_UP Vector3{0, 1, 0}
#define VECTOR3_DOWN Vector3{0, -1, 0}
#define VECTOR3_RIGHT Vector3{1, 0, 0}
#define VECTOR3_LEFT Vector3{-1, 0, 0}
#define VECTOR3_FORWARD Vector3{0, 0, 1}
#define VECTOR3_BACKWARD Vector3{0, 0, -1}

#endif