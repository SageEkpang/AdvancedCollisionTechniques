#pragma once
#ifndef STRUCTURES_H
#define STRUCTURES_H

// NOTE: LIBRARY INCLUDE(s)
#include <windows.h>
#include <cstring>
#include <d3d11.h>
#include <directxmath.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxcolors.h>
#include "DDSTextureLoader.h"
#include "resource.h"

// NOTE: GUI INCLUDE(s)
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

// NOTE: LANGUAGE INCLUDE(s) (C++)
#include <algorithm>
#include <array>
#include <condition_variable>
#include <functional>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <limits>
#include <cassert>
#include <cinttypes>
#include <memory>
#include <map>
#include <mutex>
#include <unordered_map>
#include <thread>
#include <queue>
#include <random>
#include <utility>
#include <vector>

using namespace DirectX;
using namespace std;

// PHYSICS DATA(s)

enum MaterialTypes
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

enum DragShapeTypes
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

enum PhysicTag
{
	NONE,
	PHYSICS_STATIC,
	PHYSICS_DYNAMIC,
	PHYSICS_KINEMATIC
};

enum ColliderType
{
	COLLIDER_NONE,
	COLLIDER_BOX,
	COLLIDER_PLANE,
	COLLIDER_SPHERE,
	COLLIDER_OBB,
	COLLIDER_MESH
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
}Tag;

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


	//float operator[] (int value)
	//{
	//	if (value == 0) { return this->x; }
	//	if (value == 1) { return this->y; }
	//	if (value == 2) { return this->z; }
	//}

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

	Vector3 operator=(XMFLOAT3 value)
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
	float LengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	Vector3 Inverse()
	{
		this->x = -x;
		this->y = -y;
		this->z = -z;
	}

	Vector3 DistanceTo(Vector3 value)
	{
		return Vector3(value - Vector3(x, y, z));
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

	Vector3 Pow(int power) const
	{
		return Vector3(std::powf(this->x, power), std::powf(this->y, power), std::powf(this->z, power));
	}

	float Magnitude() const
	{
		return (x * x) + (y * y) + (z * z);
	}

	Vector3 Normalise()
	{
		float t_Length = this->Magnitude();
		float t_NormX = this->x / t_Length;
		float t_NormY = this->y / t_Length;
		float t_NormZ = this->z / t_Length;

		return Vector3(t_NormX, t_NormY, t_NormZ);
	}

	float Dot(Vector3 value)
	{
		return (this->x * value.x) + (this->y * value.y) + (this->z * value.z);
	}

	float DotNotNorm(Vector3 value) const
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

#define VECTOR3_UP Vector3{0, 1, 0}

#define VECTOR3_DOWN Vector3{0, -1, 0}
#define VECTOR3_FORWARD Vector3{0, 0, 1}

typedef struct Ray
{
	const Vector3 S;
	const Vector3 V;
	const float vInvLengthSquared;

	Ray(const Vector3& S, const Vector3& V)
		: S(S), V(V), vInvLengthSquared( 1 / this->V.LengthSquared())
	{

	}

}Ray;

typedef struct VertexDataSource
{
	const Vector3* ptr;
	size_t count;

	VertexDataSource(const Vector3* ptr, size_t count)
		: ptr(ptr), count(count)
	{

	}

	VertexDataSource(const std::vector<Vector3>& vec)
		: ptr(vec.data()), count(vec.size())
	{

	}

	VertexDataSource() 
		: ptr(nullptr), count(0)
	{

	}
	
	VertexDataSource& operator=(const VertexDataSource& other) = default;

	size_t size() const {
		return count;
	}

	const Vector3& operator[](size_t index) const {
		return ptr[index];
	}

	const Vector3* begin() const {
		return ptr;
	}

	const Vector3* end() const {
		return ptr + count;
	}

}VertexDataSource;

typedef struct Simplex
{
private:

	std::array<Vector3, 4> points;
	unsigned size;

public:

	Simplex()
	{
		size = 0;
	}

	Simplex& operator=(std::initializer_list<Vector3> list)
	{
		size = 0;

		for (Vector3 point : list)
		{
			points[size++] = point;
		}

		return *this;
	}

	void push_front(Vector3 point)
	{
		points = { point, points[0], points[1], points[2] };

		size = min(size + 1, 4);
	}

	Vector3& operator[](unsigned i) { return points[i]; }
	unsigned GetSize() const { return size; }

	auto begin() const { return points.begin(); }
	auto end() const { return points.end() - (4 - size); }

}Simplex3D;


// Struct for SAT Collisions
typedef struct Interval
{
	float max;
	float min;

}Interval;

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

	Vector4(Vector3 value, float distance)
	{
		this->x = value.x;
		this->y = value.y;
		this->z = value.z;
		this->w = distance;
	}

	Vector4(Vector4& value)
	{
		this->x = value.x;
		this->y = value.y;
		this->z = value.z;
		this->w = value.w;
	}

	Vector3 xyz()
	{
		return Vector3(this->x, this->y, this->z);
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

}Vector4;

typedef struct Quaternion4
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



}Quaternion4;

typedef struct Transform3D
{
	Transform3D* parent;
	Vector3 position;
	Vector3 scale;
	Vector3 rotation;

	Transform3D(Transform3D* parent = nullptr, Vector3 position = Vector3(), Vector3 scale = Vector3(), Vector3 rotation = Vector3())
	{
		this->parent = parent;
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
	}

}Transform3D;

typedef struct ContactPoint
{
	Vector3 position;
	float penetrationDepth;

	ContactPoint()
	{
		position = Vector3();
		penetrationDepth = 0.0f;
	}

}ContactPoint;

typedef struct CollisionManifold
{
	ContactPoint points[4];
	int contactPointCount;
	float penetrationDepth;

	Vector3 collisionNormal;
	bool hasCollision;

	CollisionManifold(int contactPointCount = 0, ContactPoint points = ContactPoint(), Vector3 collisionNormal = Vector3())
	{
		this->contactPointCount = contactPointCount;
		*this->points = points;
		this->collisionNormal = collisionNormal;
	}

}CollisionManifold;

typedef struct Edge
{
	Vector3 edgeStart;
	Vector3 edgeEnd;

	Edge(Vector3 edgeStart = Vector3(), Vector3 edgeEnd = Vector3())
	{
		this->edgeStart = edgeStart;
		this->edgeEnd = edgeEnd;
	}

	Edge(const Edge& value)
	{
		this->edgeStart = value.edgeStart;
		this->edgeEnd = value.edgeEnd;
	}

	Edge operator =(Edge value)
	{
		this->edgeStart = value.edgeStart;
		this->edgeEnd = value.edgeEnd;

		return *this;
	}

	bool operator ==(Edge value)
	{
		bool t_TempStart = this->edgeStart == value.edgeStart ? true : false;
		bool t_TempEnd = this->edgeEnd == value.edgeEnd ? true : false;

		return (t_TempStart && t_TempEnd);
	}

}Edge3D;

typedef struct Face // REFERRING TO A TRIANGLE FACE (CW or CWW)
{
	Vector3 v1;
	Vector3 v2;
	Vector3 v3;

	Face(Vector3 v1 = Vector3(), Vector3 v2 = Vector3(), Vector3 v3 = Vector3())
	{
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
	}

	Face(const Face& value)
	{
		this->v1 = value.v1;
		this->v2 = value.v2;
		this->v3 = value.v3;
	}

	Face operator =(Face value)
	{
		this->v1 = value.v1;
		this->v2 = value.v2;
		this->v3 = value.v3;

		return *this;
	}

}Face3D;


// GRAPHICS STRUCT(s)
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

struct Geometry
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int numberOfIndices;

	UINT vertexBufferStride;
	UINT vertexBufferOffset;
};

struct Material
{
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
	XMFLOAT4 specular;

	Material()
	{
		this->ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		this->diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		this->specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Material(XMFLOAT4 ambient, XMFLOAT4 diffuse, XMFLOAT4 specular)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
	}
};

#endif