#ifndef MATERIAL_H
#define MATERIAL_H

#include <directxmath.h>

struct Material
{
	DirectX::XMFLOAT4 ambient;
	DirectX::XMFLOAT4 diffuse;
	DirectX::XMFLOAT4 specular;

	Material()
	{
		this->ambient = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		this->diffuse = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		this->specular = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Material(DirectX::XMFLOAT4 ambient, DirectX::XMFLOAT4 diffuse, DirectX::XMFLOAT4 specular)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
	}

	// MATERIAL DEFINE(s)
	#define MATERIAL_SHINY Material(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f))
	#define MATERIAL_ROUGH

	#define MATERIAL_MAX Material(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))
	#define MATERIAL_FLAT Material(XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f))
	#define MATERIAL_WIREFRAME Material(XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f))
	#define MATERIAL_GROUND Material(XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f))

};


#endif