  #include "Particle.h"

Particle::Particle(Transform* transform, float mass, ID3D11Device* device)
{
	// NOTE: Init Transform Variable(s)
	m_World = new XMFLOAT4X4();
	m_Transform = new Transform();
	m_Mass = mass;

	// NOTE: "Draw" Particle Point
	MeshData t_Mesh;
	Geometry t_Geometry;

	t_Mesh = OBJLoader::Load((char*)"Resources\\OBJ\\sphere.obj", device);
	t_Geometry.indexBuffer = t_Mesh.IndexBuffer;
	t_Geometry.numberOfIndices = t_Mesh.IndexCount;
	t_Geometry.vertexBuffer = t_Mesh.VertexBuffer;
	t_Geometry.vertexBufferOffset = t_Mesh.VBOffset;
	t_Geometry.vertexBufferStride = t_Mesh.VBStride;

	m_Geometry = t_Geometry;

	// NOTE: Matrix Transformations
	m_Transform = transform;

	// Scale Matrix
	XMMATRIX Scale = XMMatrixScaling(transform->m_Scale.x, transform->m_Scale.y, transform->m_Scale.z);
	
	// Position Matrix
	XMMATRIX Position = XMMatrixTranslation(transform->m_Position.x, transform->m_Position.y, transform->m_Position.z);

	// Store Transform in Matrix
	XMStoreFloat4x4(m_World, Scale * Position);
}

Particle::~Particle()
{
	m_Geometry.indexBuffer = nullptr;
	m_Geometry.vertexBuffer = nullptr;
	delete m_Transform;
}

void Particle::Update(float deltaTime)
{
	// NOTE: Call the Physics Update Functions needed for this

	// Scale Matrix
	XMMATRIX t_Scale = XMMatrixScaling(m_Transform->m_Scale.x, m_Transform->m_Scale.y, m_Transform->m_Scale.z);

	// Rotation Matrix
	XMMATRIX t_Rotation = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);

	// Position Matrix
	XMMATRIX t_Position = XMMatrixTranslation(m_Transform->m_Position.x, m_Transform->m_Position.y, m_Transform->m_Position.z);

	// Store Transform in Matrix
	XMStoreFloat4x4(m_World, t_Scale * t_Rotation * t_Position); 
	CalculateAcceleration(deltaTime);
	ClearAccumulator();
}

void Particle::CalculateAcceleration(float deltaTime)
{
	// Add NetForce to Acceleration
	m_Acceleration += m_NetForce; // / m_Mass

	// Get position and add it to the velocity of the object
	Vector3 t_Position = m_Transform->m_Position;
	m_Velocity += m_Acceleration * deltaTime;

	// Change position based on velocity and set new position based on velocity
	t_Position += m_Velocity * deltaTime;
	m_Transform->m_Position = t_Position;
}

void Particle::ClearAccumulator()
{
	// NOTE: Reset Net Force
	m_NetForce = VECTOR3_ZERO;
	m_Acceleration = VECTOR3_ZERO;
}

void Particle::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device, Vector3 colour)
{
	// pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
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
	constantBufferData.surface.DiffuseMtrl = XMFLOAT4(colour.x, colour.y, colour.z, 1);
	constantBufferData.surface.SpecularMtrl = XMFLOAT4(0, 0, 0, 0);

	XMMATRIX temp = XMLoadFloat4x4(m_World);
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

