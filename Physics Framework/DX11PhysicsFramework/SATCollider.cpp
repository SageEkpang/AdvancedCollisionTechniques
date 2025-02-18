#include "SATCollider.h"
#include "BoxCollider.h"


SATCollider::SATCollider(char* fileName, Transform* transform, Vector3 rotation, float mass, ID3D11Device* device)
{
	printf("SAT Collider Set Up");

	// NOTE: Init variables
	m_Transform = new Transform();
	m_Transform = transform;
	m_Rotation = rotation;

	m_Mass = mass;

	// NOTE: Init the Geometry
	MeshData t_Mesh;
	Geometry t_Geometry;
	t_Mesh = OBJLoader::Load(fileName, device);
	t_Geometry.indexBuffer = t_Mesh.IndexBuffer;
	t_Geometry.numberOfIndices = t_Mesh.IndexCount;
	t_Geometry.vertexBuffer = t_Mesh.VertexBuffer;
	t_Geometry.vertexBufferOffset = t_Mesh.VBOffset;
	t_Geometry.vertexBufferStride = t_Mesh.VBStride;
	m_Geometry = t_Geometry;
}

SATCollider::~SATCollider()
{
	
}

void SATCollider::Update(float deltaTime)
{
	// NOTE: Acceleration Calculation
	CalculateAcceleration(deltaTime);
	m_Transform->Update(deltaTime);

	ClearAccumulator();
}

void SATCollider::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
	D3D11_RASTERIZER_DESC cmdesc;
	ID3D11RasterizerState* m_NormalCull;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_NONE;
	cmdesc.FrontCounterClockwise = false;
	device->CreateRasterizerState(&cmdesc, &m_NormalCull);

	pImmediateContext->RSSetState(m_NormalCull);

	// Draw Render Object
	constantBufferData.surface.AmbientMtrl = XMFLOAT4(0, 0, 0, 1);
	constantBufferData.surface.DiffuseMtrl = XMFLOAT4(1.0, 0.0, 1.0, 1);
	constantBufferData.surface.SpecularMtrl = XMFLOAT4(0, 0, 0, 0);

	XMMATRIX temp = m_Transform->GetWorldMatrix();
	constantBufferData.World = XMMatrixTranspose(temp);
	constantBufferData.HasTexture = 0.0f;

	D3D11_MAPPED_SUBRESOURCE t_ObjectMappedSubresource;
	pImmediateContext->Map(constBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_ObjectMappedSubresource);
	memcpy(t_ObjectMappedSubresource.pData, &constantBufferData, sizeof(constantBufferData));
	pImmediateContext->Unmap(constBuff, 0);

	pImmediateContext->IASetVertexBuffers(0, 1, &m_Geometry.vertexBuffer, &m_Geometry.vertexBufferStride, &m_Geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(m_Geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(m_Geometry.numberOfIndices, 0, 0);
}

void SATCollider::CalculateAcceleration(float deltaTime)
{
	// Add NetForce to Acceleration
	m_Acceleration += m_NetForce; // / m_Mass

	// Get position and add it to the velocity of the object
	Vector3 t_Position = m_Transform->GetPosition();
	m_Velocity += m_Acceleration * deltaTime;

	// Change position based on velocity and set new position based on velocity
	t_Position += m_Velocity * deltaTime;
	m_Transform->SetPosition(t_Position);
}

void SATCollider::ClearAccumulator()
{
	// NOTE: Reset Net Force
	m_NetForce = VECTOR3_ZERO;
	m_Acceleration = VECTOR3_ZERO;
}

bool SATCollider::ObjectCollisionAlt(SATCollider objectA, SATCollider objectB, CollisionManifold& out)
{
	// NOTE: Fill Orientation Array (A)
	float t_OrA[9];
	{
		t_OrA[0] = objectA.GetRotation().x;
		t_OrA[1] = 0;
		t_OrA[2] = 0;

		t_OrA[3] = 0;
		t_OrA[4] = objectA.GetRotation().y;
		t_OrA[5] = 0;

		t_OrA[6] = 0;
		t_OrA[7] = 0;
		t_OrA[8] = objectA.GetRotation().z;
	}

	// NOTE: Fill Orientation Array (B)
	float t_OrB[9];
	{
		t_OrB[0] = objectB.GetRotation().x;
		t_OrB[1] = 0;
		t_OrB[2] = 0;

		t_OrB[3] = 0;
		t_OrB[4] = objectB.GetRotation().y;
		t_OrB[5] = 0;

		t_OrB[6] = 0;
		t_OrB[7] = 0;
		t_OrB[8] = objectB.GetRotation().z;
	}

	// NOTE: Set up tests
	Vector3 t_Test[15] = {
		Vector3(t_OrA[0], t_OrA[1], t_OrA[2]),
		Vector3(t_OrA[3], t_OrA[4], t_OrA[5]),
		Vector3(t_OrA[6], t_OrA[7], t_OrA[8]),

		Vector3(t_OrB[0], t_OrB[1], t_OrB[2]),
		Vector3(t_OrB[3], t_OrB[4], t_OrB[5]),
		Vector3(t_OrB[6], t_OrB[7], t_OrB[8])
	};

	// NOTE: Insert Differnet Axis into Array
	for (int i = 0; i < 3; ++i)
	{
		t_Test[6 + i * 3 + 0] = Vector::CalculateCrossProductV(t_Test[i], t_Test[0]);
		t_Test[6 + i * 3 + 1] = Vector::CalculateCrossProductV(t_Test[i], t_Test[1]);
		t_Test[6 + i * 3 + 2] = Vector::CalculateCrossProductV(t_Test[i], t_Test[2]);
	}

	// NOTE: Do the Seperating Axis Tests
	for (int i = 0; i < 15; ++i)
	{
		bool t_Overlapping = OverlapOnAxis(objectA, objectB, t_Test[i]);
		if (!t_Overlapping)
		{
			return false; // Seperating Axis was found (There is not a collision)
		}
	}

	out.hasCollision = true;
	out.collisionNormal = objectA.GetPosition() - objectB.GetPosition();
	out.penetrationDepth;

	return true; // Seperating Axis not Found (There was Collision)
}

bool SATCollider::OverlapOnAxis(SATCollider& satA, SATCollider& satB, Vector3& axis)
{
	Interval t_A = GetIntervalOr(satA, axis);
	Interval t_B = GetIntervalOr(satB, axis);
	bool t_ExtentCheck = (t_B.min <= t_A.max) && (t_A.min <= t_B.max);

	return t_ExtentCheck;
}

Interval SATCollider::GetIntervalOr(SATCollider& sat, Vector3& axis)
{
	Vector3 t_Vertex[8];
	Vector3 t_Position = sat.GetPosition();
	Vector3 t_Size = sat.GetScale();

	// NOTE: Init Rotation Function
	float t_Orientation[9];
	{
		t_Orientation[0] = sat.GetRotation().x;
		t_Orientation[1] = 0;
		t_Orientation[2] = 0;

		t_Orientation[3] = 0;
		t_Orientation[4] = sat.GetRotation().y;
		t_Orientation[5] = 0;

		t_Orientation[6] = 0;
		t_Orientation[7] = sat.GetRotation().z;
		t_Orientation[8] = 1;
	}

	Vector3 t_Axis[] = {
		Vector3(t_Orientation[0], t_Orientation[1], t_Orientation[2]),
		Vector3(t_Orientation[3], t_Orientation[4], t_Orientation[5]),
		Vector3(t_Orientation[6], t_Orientation[7], t_Orientation[8])
	};

	t_Vertex[0] = (t_Position + t_Axis[0] * t_Size.x + t_Axis[1] * t_Size.y + t_Axis[2] * t_Size.z);
	t_Vertex[1] = (t_Position - t_Axis[0] * t_Size.x + t_Axis[1] * t_Size.y + t_Axis[2] * t_Size.z);
	t_Vertex[2] = (t_Position + t_Axis[0] * t_Size.x - t_Axis[1] * t_Size.y + t_Axis[2] * t_Size.z);
	t_Vertex[3] = (t_Position + t_Axis[0] * t_Size.x + t_Axis[1] * t_Size.y - t_Axis[2] * t_Size.z);
	t_Vertex[4] = (t_Position - t_Axis[0] * t_Size.x - t_Axis[1] * t_Size.y - t_Axis[2] * t_Size.z);
	t_Vertex[5] = (t_Position + t_Axis[0] * t_Size.x - t_Axis[1] * t_Size.y - t_Axis[2] * t_Size.z);
	t_Vertex[6] = (t_Position - t_Axis[0] * t_Size.x + t_Axis[1] * t_Size.y - t_Axis[2] * t_Size.z);
	t_Vertex[7] = (t_Position - t_Axis[0] * t_Size.x - t_Axis[1] * t_Size.y + t_Axis[2] * t_Size.z);

	Interval t_Result;
	t_Result.max = Vector::CalculateDotProduct(axis, t_Vertex[0]);
	t_Result.min = Vector::CalculateDotProduct(axis, t_Vertex[0]);

	for (int i = 1; i < 8; ++i)
	{
		float t_Projection = Vector::CalculateDotProduct(axis, t_Vertex[i]);
		t_Result.min = (t_Projection < t_Result.min) ? t_Projection : t_Result.min;
		t_Result.max = (t_Projection > t_Result.max) ? t_Projection : t_Result.max;
	}

	return t_Result;
}
