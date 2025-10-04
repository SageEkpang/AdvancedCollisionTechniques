#include "SphereCollider.h"
#include "GameObjectEntity.h"

SphereCollider::SphereCollider(Vector3 offset, float radius)
{
    m_Offset = offset;
    m_Radius = radius;
}

SphereCollider::SphereCollider(float x_offset, float y_offset, float z_offset, float radius)
{
    m_Offset = Vector3(x_offset, y_offset, z_offset);
    m_Radius = radius;
}

SphereCollider::SphereCollider(float radius)
{
    m_Offset = Vector3(0, 0, 0);
    m_Radius = radius;
}

void SphereCollider::Update(float deltaTime)
{
    // NOTE: Scale Matrix
    XMMATRIX Scale = XMMatrixScaling(m_Radius, m_Radius, m_Radius);

    // NOTE: Orientation Matrix
    XMMATRIX Orientation = XMMatrixRotationQuaternion(XMVectorSet(m_Owner->m_Transform.m_Orientation.x, m_Owner->m_Transform.m_Orientation.y, m_Owner->m_Transform.m_Orientation.z, m_Owner->m_Transform.m_Orientation.w));

    // NOTE: Position Matrix
    XMMATRIX Position = XMMatrixTranslation(m_Owner->m_Transform.m_Position.x + m_Offset.x, m_Owner->m_Transform.m_Position.y + m_Offset.y, m_Owner->m_Transform.m_Position.z + m_Offset.z);

    UpdateVertices(Vector3(m_Radius, m_Radius, m_Radius), m_Owner->m_Transform.m_Position + m_Offset);

    XMStoreFloat4x4(m_World, Scale * Orientation * Position);
}

SphereCollider::SphereCollider()
{
    m_Offset = Vector3(0, 0, 0);
    m_Radius = 1.f;
}

void SphereCollider::Construct(Vector3 offset, float radius, ID3D11Device* device)
{
    m_Offset = offset;
    m_Radius = radius;

    Geometry t_Geometry = Geometry();
    MeshData t_Mesh;

    // NOTE: Set the Mesh
    std::string t_tempMeshString = "Resources\\OBJ\\sphere.obj";

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

void SphereCollider::Construct(float x_offset, float y_offset, float z_offset, float radius, ID3D11Device* device)
{
    m_Offset = Vector3(x_offset, y_offset, z_offset);
    m_Radius = radius;

    Geometry t_Geometry = Geometry();
    MeshData t_Mesh;

    // NOTE: Set the Mesh
    std::string t_tempMeshString = "Resources\\OBJ\\sphere.obj";

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

void SphereCollider::Construct(float radius, ID3D11Device* device)
{
    m_Offset = Vector3(0, 0, 0);
    m_Radius = radius;

    Geometry t_Geometry = Geometry();
    MeshData t_Mesh;

    // NOTE: Set the Mesh
    std::string t_tempMeshString = "Resources\\OBJ\\sphere.obj";

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
