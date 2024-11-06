#include "BasicScreen.h"

BasicScreen::BasicScreen(std::string screenName)
	: Screen(screenName)
{
	// May need to add camera to this
	m_ScreenName = screenName;



	// GameObject* t_GameObject = new GameObject("Floor")

	//Geometry herculesGeometry;
	//MeshData _objMeshData;
	//_objMeshData = OBJLoader::Load("Resources\\OBJ\\donut.obj", _device);
	//herculesGeometry.indexBuffer = _objMeshData.IndexBuffer;
	//herculesGeometry.numberOfIndices = _objMeshData.IndexCount;
	//herculesGeometry.vertexBuffer = _objMeshData.VertexBuffer;
	//herculesGeometry.vertexBufferOffset = _objMeshData.VBOffset;
	//herculesGeometry.vertexBufferStride = _objMeshData.VBStride;




}

BasicScreen::~BasicScreen()
{
	Screen::~Screen();
}

void BasicScreen::Update(Camera* camera, float deltaTime)
{



}

void BasicScreen::Draw()
{

}
