#pragma once

#ifndef RENDER_H
#define RENDER_H

#include "Structures.h"
#include "OBJLoader.h"

#include "Transform.h"

class Render
{
private:

	Transform* m_Transform;
	Material m_Material;
	Geometry m_Geometry;
	XMFLOAT4X4* m_World;
	ID3D11ShaderResourceView* m_TextureRV = nullptr;
	bool m_RenderObject = true;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	Render(Transform* transform);

	/// <summary> Custom Constructor for Class </summary>
	Render(Geometry geometry, Material material);

	/// <summary> Default Deconstructor for Class </summary>
	~Render();


	// BASE FUNCTION(s)

	/// <summary> Default Base Update Function for Class </summary>
	void Update(float deltaTime);

	/// <summary> Default Base Draw Function for Class </summary>
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);


	// GETTER FUNCTION(s)
	Geometry GetGeometryData() const { return m_Geometry; }
	Material GetMaterial() { return m_Material; }
	ID3D11ShaderResourceView* const* GetTextureRV() { return &m_TextureRV; }


	// SETTER FUNCTION(s)
	void SetTextureRV(ID3D11ShaderResourceView* textureRV) { m_TextureRV = textureRV; }
	void SetGeometry(Geometry geometry) { m_Geometry = geometry; }
	void SetMaterial(Material material) { m_Material = material; }
	void SetGeometryAndMaterial(char* fileName, Material material, ID3D11Device* device);
	void SetTexture(const wchar_t* fileName, ID3D11Device* device);

	// HELPER FUNCTION(s)
	bool HasTexture() const { return m_TextureRV ? true : false; }
};

#endif

