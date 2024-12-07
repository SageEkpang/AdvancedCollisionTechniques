#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName, ID3D11Device* device)
	: Screen(screenName, device)
{
	m_ScreenInformation.physicsScreenState = PhysicsScreenState::STATE_BASIC_SCREEN;

	#pragma region Donut Object

	// Donut Object
	//GameObject* t_DonutObject = new GameObject(Tag("Donut", PhysicTag::PHYSICS_STATIC));
	//Render* t_DonutRender = new Render();
	//Transform* t_DonutTransform = new Transform();

	//RigidbodyObject* t_DonutRigidBody = new RigidbodyObject(t_DonutTransform, 0.0f);
	//SphereCollider* t_DonutCollider = new SphereCollider(t_DonutTransform, 5.0f);

	//t_DonutObject->SetTransform(t_DonutTransform);
	//t_DonutTransform->SetScale(1.0f, 1.0f, 1.0f);
	//t_DonutTransform->SetRotation(0.0f, 0.0f, 0.0f);
	//t_DonutTransform->SetPosition(-5.0f, 10.0f, 10.0f);

	//t_DonutObject->SetRigidbody(t_DonutRigidBody);
	//t_DonutRigidBody->SetCollider(t_DonutCollider);

	//t_DonutObject->SetRender(t_DonutRender);

	//Geometry t_DonutGeometry;
	//MeshData t_DonutMesh;

	//t_DonutMesh = OBJLoader::Load("Resources\\OBJ\\donut.obj", device);
	//t_DonutGeometry.indexBuffer = t_DonutMesh.IndexBuffer;
	//t_DonutGeometry.numberOfIndices = t_DonutMesh.IndexCount;
	//t_DonutGeometry.vertexBuffer = t_DonutMesh.VertexBuffer;
	//t_DonutGeometry.vertexBufferOffset = t_DonutMesh.VBOffset;
	//t_DonutGeometry.vertexBufferStride = t_DonutMesh.VBStride;

	//t_DonutRender->SetGeometry(t_DonutGeometry);
	//t_DonutRender->SetMaterial(MATERIAL_SHINY);

	//// Texture Data
	//ID3D11ShaderResourceView* t_DonutTexture = nullptr;
	//CreateDDSTextureFromFile(device, L"Resources\\Textures\\stone.dds", nullptr, &t_DonutTexture);

	//t_DonutRender->SetTextureRV(t_DonutTexture);

	//InsertObjectIntoList(t_DonutObject);


	#pragma endregion

	#pragma region Plane Object

	// Plane Object
	GameObject* t_PlaneObject = new GameObject(Tag("Plane", PhysicTag::PHYSICS_STATIC));
	Render* t_PlaneRender = new Render();
	Transform* t_PlaneTransform = new Transform();
	RigidbodyObject* t_PlaneRigidbody = new RigidbodyObject(t_PlaneTransform, 0.0f);
	PlaneCollider* t_PlaneCollider = new PlaneCollider(t_PlaneTransform);

	// Transform
	t_PlaneObject->SetTransform(t_PlaneTransform);
	t_PlaneTransform->SetScale(100.0f, 1.0f, 100.0f);
	t_PlaneTransform->SetPosition(0.0f, 0.0f, 10.0f);

	// Rigidbody 
	t_PlaneObject->SetRigidbody(t_PlaneRigidbody);
	t_PlaneRigidbody->SetCollider(t_PlaneCollider);

	// Collision
	t_PlaneObject->SetCollider(t_PlaneCollider);

	// Rendering
	t_PlaneObject->SetRender(t_PlaneRender);
	t_PlaneRender->SetGeometryAndMaterial("Resources\\OBJ\\plane.obj", MATERIAL_SHINY, device);
	t_PlaneRender->SetTexture(L"Resources\\Textures\\floor.dds", device);

	InsertObjectIntoList(t_PlaneObject);


	// Test Object
	GameObject* t_TestObject = new GameObject();
	SphereCollider* t_TestCollider = new SphereCollider(t_TestObject->GetTransform(), 10);

	t_TestObject = GameObject::QuickObject(Vector3(0, 7, 0), Vector3(4, 4, 4), Vector3(0, 0, 0), NULL, "Resources\\OBJ\\SpikeBall.obj", MATERIAL_SHINY, L"Resources\\Textures\\floor.dds", device);

	InsertObjectIntoList(t_TestObject);

	#pragma endregion

	#pragma region Head Object

	// Head Object
	//GameObject* t_HeadObject = new GameObject(Tag("Head", PhysicTag::PHYSICS_STATIC));
	//Render* t_HeadRender = new Render();
	//Transform* t_HeadTransform = new Transform();
	//RigidbodyObject* t_HeadRigidbody = new RigidbodyObject(t_HeadTransform, 0.0f);
	//PlaneCollider* t_HeadCollider = new PlaneCollider(t_HeadTransform);

	//t_HeadObject->SetTransform(t_HeadTransform);
	//t_HeadTransform->SetScale(0.2f, 0.2f, 0.2f);
	//t_HeadTransform->SetRotation(0.0f, 180.0f, 0.0f);
	//t_HeadTransform->SetPosition(5.0f, 5.0f, 10.0f);

	//t_HeadObject->SetRigidbody(t_HeadRigidbody);
	//t_HeadRigidbody->SetCollider(t_HeadCollider);

	//t_HeadObject->SetRender(t_HeadRender);

	//// Mesh Data
	//Geometry t_HeadGeometry;
	//MeshData t_HeadMesh;

	//t_HeadMesh = OBJLoader::Load("Resources\\OBJ\\joelModel.obj", device);
	//t_HeadGeometry.indexBuffer = t_HeadMesh.IndexBuffer;
	//t_HeadGeometry.numberOfIndices = t_HeadMesh.IndexCount;
	//t_HeadGeometry.vertexBuffer = t_HeadMesh.VertexBuffer;
	//t_HeadGeometry.vertexBufferOffset = t_HeadMesh.VBOffset;
	//t_HeadGeometry.vertexBufferStride = t_HeadMesh.VBStride;

	//t_HeadRender->SetGeometry(t_HeadGeometry);
	//t_HeadRender->SetMaterial(MATERIAL_SHINY);

	//// Texture Data
	//ID3D11ShaderResourceView* t_HeadTexture = nullptr;
	//CreateDDSTextureFromFile(device, L"Resources\\Textures\\stone.dds", nullptr, &t_HeadTexture);

	//t_HeadRender->SetTextureRV(t_HeadTexture);

	//InsertObjectIntoList(t_HeadObject);

	#pragma endregion

	// Spike Object
	//GameObject* t_SpikeObject = new GameObject(Tag("Spike", PhysicTag::PHYSICS_STATIC));
	//Render* t_SpikeRender = new Render();
	//Transform* t_SpikeTransform = new Transform();
	//RigidbodyObject* t_SpikeRigidbody = new RigidbodyObject(t_SpikeTransform, 0.0f);
	//Collider* t_SpikeCollider = new SphereCollider(t_SpikeTransform, 10.0);

	//t_SpikeObject->SetTransform(t_SpikeTransform);
	//t_SpikeTransform->SetScale(1.0f, 1.0f, 1.0f);
	//t_SpikeTransform->SetRotation(0.0f, 0.0f, 0.0f);
	//t_SpikeTransform->SetPosition(15.0f, 5.0f, 10.0f);

	//t_SpikeObject->SetRigidbody(t_SpikeRigidbody);
	//t_SpikeObject->SetCollider(t_SpikeCollider);

	//t_SpikeRigidbody->SetCollider(t_SpikeCollider);

	//t_SpikeObject->SetRender(t_SpikeRender);

	//// Mesh Data
	//Geometry t_SpikeGeometry;
	//MeshData t_SpikeMesh;

	//t_SpikeMesh = OBJLoader::Load("Resources\\OBJ\\SpikeBall.obj", device);
	//t_SpikeGeometry.indexBuffer = t_SpikeMesh.IndexBuffer;
	//t_SpikeGeometry.numberOfIndices = t_SpikeMesh.IndexCount;
	//t_SpikeGeometry.vertexBuffer = t_SpikeMesh.VertexBuffer;
	//t_SpikeGeometry.vertexBufferOffset = t_SpikeMesh.VBOffset;
	//t_SpikeGeometry.vertexBufferStride = t_SpikeMesh.VBStride;

	//t_SpikeRender->SetGeometry(t_SpikeGeometry);
	//t_SpikeRender->SetMaterial(MATERIAL_MAX);

	//// Texture Data
	//ID3D11ShaderResourceView* t_SpikeTexture = nullptr;
	//CreateDDSTextureFromFile(device, L"Resources\\Textures\\stone.dds", nullptr, &t_SpikeTexture);

	//t_SpikeRender->SetTextureRV(t_SpikeTexture);

	//InsertObjectIntoList(t_SpikeObject);
}

BasicScreen::~BasicScreen()
{
	Screen::~Screen();



}

void BasicScreen::Update(float deltaTime)
{
	Screen::Update(deltaTime);




}
