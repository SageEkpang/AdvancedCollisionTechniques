#include "ConvexHullScreen.h"

ConvexHullScreen::ConvexHullScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_CONVEX_HULL_SCREEN;

	// Spike Object
	GameObject* t_SpikeObject = new GameObject(Tag("Spike", PhysicTag::PHYSICS_STATIC));
	Transform* t_SpikeTransform = new Transform();
	Render* t_SpikeRender = new Render(t_SpikeTransform);
	RigidbodyObject* t_SpikeRigidbody = new RigidbodyObject(t_SpikeTransform, 0.0f);
	PlaneCollider* t_SpikeCollider = new PlaneCollider(t_SpikeTransform);

	t_SpikeObject->SetTransform(t_SpikeTransform);
	t_SpikeTransform->SetScale(1.0f, 1.0f, 1.0f);
	t_SpikeTransform->SetRotation(0.0f, 0.0f, 0.0f);
	t_SpikeTransform->SetPosition(15.0f, 5.0f, 10.0f);

	t_SpikeObject->SetRigidbody(t_SpikeRigidbody);
	t_SpikeRigidbody->SetCollider(t_SpikeCollider);

	t_SpikeObject->SetRender(t_SpikeRender);

	// Mesh Data
	Geometry t_SpikeGeometry;
	MeshData t_SpikeMesh;

	t_SpikeMesh = OBJLoader::Load("Resources\\OBJ\\SpikeBall.obj", device);
	t_SpikeGeometry.indexBuffer = t_SpikeMesh.IndexBuffer;
	t_SpikeGeometry.numberOfIndices = t_SpikeMesh.IndexCount;
	t_SpikeGeometry.vertexBuffer = t_SpikeMesh.VertexBuffer;
	t_SpikeGeometry.vertexBufferOffset = t_SpikeMesh.VBOffset;
	t_SpikeGeometry.vertexBufferStride = t_SpikeMesh.VBStride;

	t_SpikeRender->SetGeometry(t_SpikeGeometry);
	t_SpikeRender->SetMaterial(MATERIAL_SHINY);

	// Texture Data
	ID3D11ShaderResourceView* t_SpikeTexture = nullptr;
	CreateDDSTextureFromFile(device, L"Resources\\Textures\\stone.dds", nullptr, &t_SpikeTexture);

	t_SpikeRender->SetTextureRV(t_SpikeTexture);

	m_GameObjects.push_back(t_SpikeObject);
}

ConvexHullScreen::~ConvexHullScreen()
{
	Screen::~Screen();
}

void ConvexHullScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);
}

