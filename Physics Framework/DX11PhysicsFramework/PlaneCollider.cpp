#include "PlaneCollider.h"
#include "GameObjectEntity.h"

PlaneCollider::PlaneCollider(Vector3 offset, Vector3 scale)
{
	m_Offset = offset;
	m_Scale = scale;
}

PlaneCollider::PlaneCollider(Vector3 offset, float width, float height, float length)
{
	m_Offset = offset;
	m_Scale = Vector3(width, height, length);
}

PlaneCollider::PlaneCollider(Vector3 scale)
{
	m_Offset = Vector3(0, 0, 0);
	m_Scale = scale;
}

PlaneCollider::PlaneCollider(float x_offset, float y_offset, float z_offset, float width, float height, float length)
{
	m_Offset = Vector3(x_offset, y_offset, z_offset);
	m_Scale = Vector3(width, height, length);
}

PlaneCollider::PlaneCollider()
{
	m_Offset = Vector3(0, 0, 0);
	m_Scale = Vector3(1, 1, 1);
}

void PlaneCollider::Construct(Vector3 offset, Vector3 scale, ID3D11Device* device)
{
	m_Offset = offset;
	m_Scale = scale;

	Geometry t_Geometry = Geometry();
	MeshData t_Mesh;

	// NOTE: Set the Mesh
	std::string t_tempMeshString = "Resources\\OBJ\\plane.obj";

	FillVerticesArray((char*)t_tempMeshString.c_str());

	t_Mesh = OBJLoader::Load(t_tempMeshString.data(), device);
	t_Geometry.indexBuffer = t_Mesh.IndexBuffer;
	t_Geometry.numberOfIndices = t_Mesh.IndexCount;
	t_Geometry.vertexBuffer = t_Mesh.VertexBuffer;
	t_Geometry.vertexBufferOffset = t_Mesh.VBOffset;
	t_Geometry.vertexBufferStride = t_Mesh.VBStride;

	m_Geometry = t_Geometry;
	m_Material = MATERIAL_WIREFRAME;
}

void PlaneCollider::Construct(Vector3 offset, float width, float height, float length, ID3D11Device* device)
{
	m_Offset = offset;
	m_Scale = Vector3(width, height, length);

	Geometry t_Geometry = Geometry();
	MeshData t_Mesh;

	// NOTE: Set the Mesh
	std::string t_tempMeshString = "Resources\\OBJ\\plane.obj";

	FillVerticesArray((char*)t_tempMeshString.c_str());

	t_Mesh = OBJLoader::Load(t_tempMeshString.data(), device);
	t_Geometry.indexBuffer = t_Mesh.IndexBuffer;
	t_Geometry.numberOfIndices = t_Mesh.IndexCount;
	t_Geometry.vertexBuffer = t_Mesh.VertexBuffer;
	t_Geometry.vertexBufferOffset = t_Mesh.VBOffset;
	t_Geometry.vertexBufferStride = t_Mesh.VBStride;

	m_Geometry = t_Geometry;
	m_Material = MATERIAL_WIREFRAME;
}

void PlaneCollider::Construct(Vector3 scale, ID3D11Device* device)
{
	m_Offset = Vector3(0, 0, 0);
	m_Scale = scale;

	Geometry t_Geometry = Geometry();
	MeshData t_Mesh;

	// NOTE: Set the Mesh
	std::string t_tempMeshString = "Resources\\OBJ\\plane.obj";

	FillVerticesArray((char*)t_tempMeshString.c_str());

	t_Mesh = OBJLoader::Load(t_tempMeshString.data(), device);
	t_Geometry.indexBuffer = t_Mesh.IndexBuffer;
	t_Geometry.numberOfIndices = t_Mesh.IndexCount;
	t_Geometry.vertexBuffer = t_Mesh.VertexBuffer;
	t_Geometry.vertexBufferOffset = t_Mesh.VBOffset;
	t_Geometry.vertexBufferStride = t_Mesh.VBStride;

	m_Geometry = t_Geometry;
	m_Material = MATERIAL_WIREFRAME;
}

void PlaneCollider::Construct(float x_offset, float y_offset, float z_offset, float width, float height, float length, ID3D11Device* device)
{
	m_Offset = Vector3(x_offset, y_offset, z_offset);
	m_Scale = Vector3(width, height, length);

	Geometry t_Geometry = Geometry();
	MeshData t_Mesh;

	// NOTE: Set the Mesh
	std::string t_tempMeshString = "Resources\\OBJ\\plane.obj";

	FillVerticesArray((char*)t_tempMeshString.c_str());

	t_Mesh = OBJLoader::Load(t_tempMeshString.data(), device);
	t_Geometry.indexBuffer = t_Mesh.IndexBuffer;
	t_Geometry.numberOfIndices = t_Mesh.IndexCount;
	t_Geometry.vertexBuffer = t_Mesh.VertexBuffer;
	t_Geometry.vertexBufferOffset = t_Mesh.VBOffset;
	t_Geometry.vertexBufferStride = t_Mesh.VBStride;

	m_Geometry = t_Geometry;
	m_Material = MATERIAL_WIREFRAME;
}

void PlaneCollider::Update(float deltaTime)
{
	// NOTE: Scale Matrix
	XMMATRIX Scale = XMMatrixScaling(m_Scale.x, 1, m_Scale.z);

	// NOTE: Orientation Matrix
	XMMATRIX Orientation = XMMatrixRotationQuaternion(XMVectorSet(m_Owner->m_Transform.m_Orientation.x, m_Owner->m_Transform.m_Orientation.y, m_Owner->m_Transform.m_Orientation.z, m_Owner->m_Transform.m_Orientation.w));

	// NOTE: Position Matrix
	XMMATRIX Position = XMMatrixTranslation(m_Owner->m_Transform.m_Position.x + m_Offset.x, m_Owner->m_Transform.m_Position.y + m_Offset.y, m_Owner->m_Transform.m_Position.z + m_Offset.z);

	UpdateVertices(Vector3(m_Scale.x, 1, m_Scale.y), m_Owner->m_Transform.m_Position + m_Offset);

	XMStoreFloat4x4(m_World, Scale * Orientation * Position);
}

inline Vector3 PlaneCollider::GetNormal()
{



	// m_Owner->m_Transform.GetRotation();


	return Vector3();
}

Vector3 PlaneCollider::GetMax()
{
	return (m_Owner->m_Transform.m_Position + m_Offset) + ((m_Owner->m_Transform.m_Scale * m_Scale) / 2);
}

Vector3 PlaneCollider::GetMin()
{
	return (m_Owner->m_Transform.m_Position + m_Offset) - ((m_Owner->m_Transform.m_Scale * m_Scale) / 2);
}