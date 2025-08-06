#ifndef MESH_H
#define MESH_H

#include "Structures.h"
#include "OBJLoader.h"

#include "ComponentEntity.h"
#include "Material.h"
#include "Geometry.h"

class Mesh : public ComponentEntity
{
private:

	Material m_Material;
	Geometry m_Geometry;
	bool m_RenderObject = true;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	Mesh(Geometry geometry, Material material);

	/// <summary> Default Deconstructor for Class </summary>
	~Mesh();


	// BASE FUNCTION(s)

	/// <summary> Default Base Update Function for Class </summary>
	void Update(float deltaTime) { };

	/// <summary> Default Base Draw Function for Class </summary>
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);

	// GETTER FUNCTION(s)
	Geometry GetGeometryData() const { return m_Geometry; }
	Material GetMaterial() { return m_Material; }

	// SETTER FUNCTION(s)
	void SetGeometry(Geometry geometry) { m_Geometry = geometry; }
	void SetMaterial(Material material) { m_Material = material; }
	void SetGeometryAndMaterial(char* fileName, Material material, ID3D11Device* device);
};

#endif

