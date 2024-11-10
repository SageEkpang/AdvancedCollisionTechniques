#pragma once

#ifndef RENDER_H
#define RENDER_H

#include "Structures.h"

class Render
{
private:

	Material m_Material;
	Geometry m_Geometry;
	ID3D11ShaderResourceView* m_TextureRV = nullptr;

public:

	// CLASS FUNCTION(s)

	/// <summary> Default Constructor for Class </summary>
	Render();

	/// <summary> Custom Constructor for Class </summary>
	Render(Geometry geometry, Material material);

	/// <summary> Default Deconstructor for Class </summary>
	~Render();


	// BASE FUNCTION(s)

	/// <summary> Default Base Update Function for Class </summary>
	void Update(float DeltaTime) { }

	/// <summary> Default Base Draw Function for Class </summary>
	void Draw(ID3D11DeviceContext* pImmediateContext);


	// GETTER FUNCTION(s)
	Geometry GetGeometryData() const { return m_Geometry; }
	Material GetMaterial() { return m_Material; }
	ID3D11ShaderResourceView* const* GetTextureRV() { return &m_TextureRV; }


	// SETTER FUNCTION(s)
	void SetTextureRV(ID3D11ShaderResourceView* textureRV) { m_TextureRV = textureRV; }
	void SetGeometry(Geometry geometry) { m_Geometry = geometry; }
	void SetMaterial(Material material) { m_Material = material; }


	// HELPER FUNCTION(s)
	bool HasTexture() const { return m_TextureRV ? true : false; }
};

#endif

