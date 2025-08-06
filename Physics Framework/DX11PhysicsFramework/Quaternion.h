#ifndef QUATERNION_H
#define QUATERNION_H

#include "Constants.h"
#include "Vector3.h"

struct Quaternion4
{
	float x, y, z, w;

	Quaternion4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion4(const Quaternion4& value)
	{
		this->x = value.x;
		this->y = value.y;
		this->z = value.z;
		this->w = value.w;
	}

	Quaternion4 operator+=(Quaternion4 value)
	{
		this->x += value.x;
		this->y += value.y;
		this->z += value.z;
		this->w += value.w;
		return *this;
	}

	Quaternion4 operator-=(Quaternion4 value)
	{
		this->x -= value.x;
		this->y -= value.y;
		this->z -= value.z;
		this->w -= value.w;
		return *this;
	}

	Quaternion4 operator*=(Quaternion4 value)
	{
		this->x *= value.x;
		this->y *= value.y;
		this->z *= value.z;
		this->w *= value.w;
		return *this;
	}

	Quaternion4 operator/=(float value)
	{
		this->x /= value;
		this->y /= value;
		this->z /= value;
		this->w /= value;
		return *this;
	}


	Quaternion4 operator~()
	{
		return Quaternion4(-x, -y, -z, w);
	}

	Quaternion4 operator+(Quaternion4 value)
	{
		return Quaternion4(x + value.x, y + value.y, z + value.z, w + value.w);
	}

	Quaternion4 operator-(Quaternion4 value)
	{
		return Quaternion4(x - value.x, y - value.y, z - value.z, w - value.w);
	}

	Quaternion4 operator*(Quaternion4 value)
	{
		return Quaternion4(
			w * value.x + x * value.w + y * value.z - z * value.y, // X
			w * value.y + y * value.w + z * value.x - x * value.z, // Y
			w * value.z + z * value.w + x * value.y - y * value.x, // Z
			w * value.w - x * value.x - y * value.y - z * value.z // W
		);
	}

	Quaternion4 operator*(float value)
	{
		return Quaternion4(x * value, y * value, z * value, w * value);
	}

	Quaternion4 operator*(Vector3 value)
	{
		return Quaternion4(
			w * value.x + y * value.z - z * value.y, // X
			w * value.y + z * value.x - x * value.z, // Y
			w * value.z + x * value.y - y * value.x, // Z
			-(x * value.x + y * value.y + z * value.z) // W
		);
	}

	Quaternion4 operator/(float value)
	{
		return Quaternion4(x / value, y / value, z / value, w / value);
	}

	float Magnitude(void)
	{
		return (float)sqrt(w * w + x * x + y * y + z * z);
	}

	Vector3 GetVector3()
	{
		return Vector3(x, y, z);
	}

	float GetScalar(void)
	{
		return w;
	}

	Quaternion4 Abs()
	{
		this->x = std::abs(x);
		this->y = std::abs(y);
		this->z = std::abs(z);
		this->w = std::abs(w);
		return *this;
	}

};

struct Quaternion
{

    static float QGetAngle(Quaternion4 q);
    static Vector3 QGetAxis(Quaternion4 q);

    static Quaternion4 QRotate(Quaternion4 q1, Quaternion4 q2);
    static Vector3 QVRotate(Quaternion4 q, Vector3 v);

    static float DegreesToRadians(float deg);
    static float RadiansToDegrees(float rad);

    static Quaternion4 MakeQFromEulerAngles(float x, float y, float z);
    static Vector3 MakeEulerAnglesFromQ(Quaternion4 q);
};

#endif
