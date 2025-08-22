#ifndef MESH_H
#define MESH_H

#include "OBJLoader.h"
#include "DDSTextureLoader.h"

#include "ComponentEntity.h"
#include "Material.h"
#include "Geometry.h"
#include "Constants.h"
#include "Vector4.h"
#include <string>

class Mesh : public ComponentEntity
{
private:

	DirectX::XMFLOAT4X4* m_World;
	ID3D11ShaderResourceView* m_ShaderResource = nullptr;

public:

	Material m_Material;
	Geometry m_Geometry;
	bool m_RenderMesh = true;

public:

	// CLASS FUNCTION (Components)
	void Construct(std::string meshFileName, ID3D11Device* device);
	void Construct(std::string meshFileName, Material material, ID3D11Device* device);
	void Construct(std::string meshFileName, Vector4 colour, ID3D11Device* device);
	void Construct(std::string meshFileName, std::string textureFileName, ID3D11Device* device);

	void SetTexture(std::string textureFileName, ID3D11Device* device);


	// CLASS FUNCTION (Generals)
	/// <summary> Default Constructor for Class </summary>
	Mesh();

	/// <summary> Default Deconstructor for Class </summary>
	~Mesh();


	// BASE FUNCTION(s)

	/// <summary> Default Base Update Function for Class </summary>
	void Update(float deltaTime) override;

	/// <summary> Default Base Draw Function for Class </summary>
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device) override;
};

#endif

