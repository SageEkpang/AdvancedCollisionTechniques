#ifndef VECTOR4_H
#define VECTOR4_H

struct Vector4
{
	union { float x, r; };
	union { float y, g; };
	union { float z, b; };
	union { float w, a; };

	Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4(const Vector4& value)
	{
		this->x = value.x;
		this->y = value.y;
		this->z = value.z;
		this->w = value.w;
	}

	Vector4 operator+(Vector4 value)
	{
		return Vector4(x + value.x, y + value.y, z + value.z, w + value.w);
	}

	Vector4 operator-(Vector4 value)
	{
		return Vector4(x - value.x, y - value.y, z - value.z, w - value.w);
	}

	Vector4 operator++()
	{
		++x;
		++y;
		++z;
		++w;
		return *this;
	}

	Vector4 operator--()
	{
		--x;
		--y;
		--z;
		--w;

		return *this;
	}

	Vector4 operator*(Vector4 value)
	{
		return Vector4(x * value.x, y * value.y, z * value.z, w * value.w);
	}
};

#endif
