#pragma once
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <windows.h>
#include <cstring>
#include <d3d11.h>
#include <directxmath.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxcolors.h>
#include "DDSTextureLoader.h"
#include "resource.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <array>

using namespace DirectX;
using namespace std;

// CUSTOM DATA(s)

enum PhysicsScreenState
{
	STATE_NONE = 0,
	STATE_BASIC_SCREEN
};

enum ScreenState
{
	SCREEN_NEXT = 1,
	SCREEN_CURRENT = 0,
	SCREEN_PREVIOUS = -1
};

enum PhysicTag
{
	NONE,
	PHYSICS_STATIC,
	PHYSICS_DYNAMIC,
	PHYSICS_KINEMATIC
};

typedef struct Tag
{
	std::string name;
	PhysicTag type;
	int id;

	Tag(std::string name = " ", PhysicTag type = PhysicTag::NONE, int id = 0)
	{
		this->name = name;
		this->type = type;
		this->id = id;
	}
};


typedef struct Vector3
{
	float x, y, z;

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


	bool operator==(Vector3 value)
	{
		bool tempX = this->x == value.x ? true : false;
		bool tempY = this->y == value.y ? true : false;
		bool tempZ = this->z == value.z ? true : false;

		if (tempX && tempY && tempZ) return true;

		return false;
	}

	Vector3 Abs()
	{
		this->x = std::abs(x);
		this->y = std::abs(y);
		this->z = std::abs(z);

		return *this;
	}

}Vector3, Vector3D;

typedef struct Vector4
{
	float x, y, z, w;

	Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4(Vector4& value)
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

}Vector4, Vector4D;

typedef struct Quaternion
{
	float x, y, z, w;

	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion(const Quaternion& value)
	{
		this->x = value.x;
		this->y = value.y;
		this->z = value.z;
		this->w = value.w;
	}

	Quaternion operator+=(Quaternion value)
	{
		this->x += value.x;
		this->y += value.y;
		this->z += value.z;
		this->w += value.w;
		return *this;
	}

	Quaternion operator-=(Quaternion value)
	{
		this->x -= value.x;
		this->y -= value.y;
		this->z -= value.z;
		this->w -= value.w;
		return *this;
	}

	Quaternion operator*=(Quaternion value)
	{
		this->x *= value.x;
		this->y *= value.y;
		this->z *= value.z;
		this->w *= value.w;
		return *this;
	}

	Quaternion operator/=(float value)
	{
		this->x /= value;
		this->y /= value;
		this->z /= value;
		this->w /= value;
		return *this;
	}


	Quaternion operator~()
	{
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion operator+(Quaternion value)
	{
		return Quaternion(x + value.x, y + value.y, z + value.z, w + value.w);
	}

	Quaternion operator-(Quaternion value)
	{
		return Quaternion(x - value.x, y - value.y, z - value.z, w - value.w);
	}

	Quaternion operator*(Quaternion value)
	{
		return Quaternion(
			w * value.x + x * value.w + y * value.z - z * value.y, // X
			w * value.y + y * value.w + z * value.x - x * value.z, // Y
			w * value.z + z * value.w + x * value.y - y * value.x, // Z
			w * value.w - x * value.x - y * value.y - z * value.z // W
		);
	}

	Quaternion operator/(float value)
	{
		return Quaternion(x / value, y / value, z / value, w / value);
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

	Quaternion Abs()
	{
		this->x = std::abs(x);
		this->y = std::abs(y);
		this->z = std::abs(z);
		this->w = std::abs(w);
		return *this;
	}

};

typedef struct Transform3D
{
	Transform3D* parent;
	Vector3 position;
	Vector3 scale;
	Vector3 rotation;

	Transform3D(Transform3D* parent = nullptr, Vector3 position = Vector3(), Vector3 scale = Vector3(), Vector3 rotation = Vector3())
	{
		parent = new Transform3D();
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
	}

}Transform3D;


struct SurfaceInfo
{
	XMFLOAT4 AmbientMtrl;
	XMFLOAT4 DiffuseMtrl;
	XMFLOAT4 SpecularMtrl;
};

struct Light
{
	XMFLOAT4 AmbientLight;
	XMFLOAT4 DiffuseLight;
	XMFLOAT4 SpecularLight;

	float SpecularPower;
	XMFLOAT3 LightVecW;
};

struct ConstantBuffer
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;

	SurfaceInfo surface;

	Light light;

	XMFLOAT3 EyePosW;
	float HasTexture;
};

struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 TexC;

	bool operator<(const SimpleVertex other) const
	{
		return memcmp((void*)this, (void*)&other, sizeof(SimpleVertex)) > 0;
	};
};

struct MeshData
{
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	UINT VBStride;
	UINT VBOffset;
	UINT IndexCount;
};

#endif