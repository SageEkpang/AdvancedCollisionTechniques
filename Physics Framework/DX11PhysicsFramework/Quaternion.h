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

	static float QGetAngle(Quaternion4 q)
	{
		return (float)(2 * acos(q.w));
	}

	static Vector3 QGetAxis(Quaternion4 q)
	{
		Vector3 v;
		float m;

		v = q.GetVector3();
		m = v.Magnitude();

		if (m <= MINTOL)
			return Vector3();
		else
			return v / m;
	}

	static Quaternion4 QRotate(Quaternion4 q1, Quaternion4 q2)
	{
		return q1 * q2 * (~q1);
	}

	static Vector3 QVRotate(Quaternion4 q, Vector3 v)
	{
		Quaternion4 t;
		t = q * v * (~q);
		return t.GetVector3();
	}

	static float DegreesToRadians(float deg)
	{
		return deg * PI / 180.0f;
	}

	static float RadiansToDegrees(float rad)
	{
		return rad * 180.0f / PI;
	}

	static Quaternion4 MakeQFromEulerAngles(float x, float y, float z)
	{
		Quaternion4     q;
		double     roll = DegreesToRadians(x);
		double     pitch = DegreesToRadians(y);
		double     yaw = DegreesToRadians(z);

		double     cyaw, cpitch, croll, syaw, spitch, sroll;
		double     cyawcpitch, syawspitch, cyawspitch, syawcpitch;

		cyaw = cos(0.5f * yaw);
		cpitch = cos(0.5f * pitch);
		croll = cos(0.5f * roll);
		syaw = sin(0.5f * yaw);
		spitch = sin(0.5f * pitch);
		sroll = sin(0.5f * roll);

		cyawcpitch = cyaw * cpitch;
		syawspitch = syaw * spitch;
		cyawspitch = cyaw * spitch;
		syawcpitch = syaw * cpitch;

		q.w = (float)(cyawcpitch * croll + syawspitch * sroll);
		q.x = (float)(cyawcpitch * sroll - syawspitch * croll);
		q.y = (float)(cyawspitch * croll + syawcpitch * sroll);
		q.z = (float)(syawcpitch * croll - cyawspitch * sroll);

		return q;
	}

	static Vector3 MakeEulerAnglesFromQ(Quaternion4 q)
	{
		double     r11, r21, r31, r32, r33, r12, r13;
		double     q00, q11, q22, q33;
		double     tmp;
		Vector3     u;

		q00 = q.w * q.w;
		q11 = q.x * q.x;
		q22 = q.y * q.y;
		q33 = q.z * q.z;

		r11 = q00 + q11 - q22 - q33;
		r21 = 2 * (q.x * q.y + q.w * q.z);
		r31 = 2 * (q.x * q.z - q.w * q.y);
		r32 = 2 * (q.y * q.z + q.w * q.x);
		r33 = q00 - q11 - q22 + q33;

		tmp = fabs(r31);
		if (tmp > 0.999999)
		{
			r12 = 2 * (q.x * q.y - q.w * q.z);
			r13 = 2 * (q.x * q.z + q.w * q.y);

			u.x = RadiansToDegrees(0.0f); //roll
			u.y = RadiansToDegrees((float)(-(PI / 2) * r31 / tmp));   // pitch
			u.z = RadiansToDegrees((float)atan2(-r12, -r31 * r13)); // yaw
			return u;
		}

		u.x = RadiansToDegrees((float)atan2(r32, r33)); // roll
		u.y = RadiansToDegrees((float)asin(-r31));      // pitch
		u.z = RadiansToDegrees((float)atan2(r21, r11)); // yaw
		return u;
	}

};

#endif
