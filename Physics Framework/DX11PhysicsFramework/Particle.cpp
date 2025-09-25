  #include "Particle.h"

Particle::Particle(Vector3 position, float mass, ID3D11Device* device)
{
	// NOTE: Init Transform Variable(s)
	m_World = new XMFLOAT4X4();
	m_Mass = mass;

	// NOTE: "Draw" Particle Point
	MeshData t_Mesh;
	Geometry t_Geometry;

	m_Position = position;

	t_Mesh = OBJLoader::Load((char*)"Resources\\OBJ\\sphere.obj", device);
	t_Geometry.indexBuffer = t_Mesh.IndexBuffer;
	t_Geometry.numberOfIndices = t_Mesh.IndexCount;
	t_Geometry.vertexBuffer = t_Mesh.VertexBuffer;
	t_Geometry.vertexBufferOffset = t_Mesh.VBOffset;
	t_Geometry.vertexBufferStride = t_Mesh.VBStride;

	m_Geometry = t_Geometry;

	// Scale Matrix
	XMMATRIX Scale = XMMatrixScaling(1, 1, 1);
	
	// Position Matrix
	XMMATRIX Position = XMMatrixTranslation(position.x, position.y, position.z);

	// Store Transform in Matrix
	XMStoreFloat4x4(m_World, Scale * Position);
}

Particle::~Particle()
{
	m_Geometry.indexBuffer = nullptr;
	m_Geometry.vertexBuffer = nullptr;
}

void Particle::Update(float deltaTime)
{
	// NOTE: Apply force to the Particles in a direction
	if (true) { m_NetForce += GravityForce(); }

	// NOTE: Call the Physics Update Functions needed for this
	CalculateAcceleration(deltaTime);
	ClearAccumulator();

	// Scale Matrix
	XMMATRIX t_Scale = XMMatrixScaling(1, 1, 1);

	// Position Matrix
	XMMATRIX t_Position = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	// Store Transform in Matrix
	XMStoreFloat4x4(m_World, t_Scale * t_Position); 
}

void Particle::CalculateAcceleration(float deltaTime)
{
	// Add NetForce to Acceleration
	m_Acceleration += m_NetForce; // / m_Mass

	// Get position and add it to the velocity of the object
	Vector3 t_Position = m_Position;
	m_Velocity += m_Acceleration * deltaTime;

	// Change position based on velocity and set new position based on velocity
	t_Position += m_Velocity * deltaTime;
	m_Position = t_Position;
}

void Particle::ClearAccumulator()
{
	// NOTE: Reset Net Force
	m_NetForce = VECTOR3_ZERO;
	m_Acceleration = VECTOR3_ZERO;
}

Vector3 Particle::GravityForce()
{
	// Calculate the Distance from Object to Ground (0, 0, 0 will always be the ground)
	Vector3 t_Gravity = (Vector3(0, 9.81, 0) * m_Mass) * -1; // NOTE: Simplified Gravity Formula
	return t_Gravity;
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

