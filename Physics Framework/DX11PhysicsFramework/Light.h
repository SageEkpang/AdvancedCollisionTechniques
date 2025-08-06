#ifndef LIGHT_H
#define LIGHT_H

#include <directxmath.h>

struct Light
{
	DirectX::XMFLOAT4 AmbientLight;
	DirectX::XMFLOAT4 DiffuseLight;
	DirectX::XMFLOAT4 SpecularLight;

	float SpecularPower;
	DirectX::XMFLOAT3 LightVecW;
};

#endif