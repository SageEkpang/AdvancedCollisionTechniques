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
};

#endif