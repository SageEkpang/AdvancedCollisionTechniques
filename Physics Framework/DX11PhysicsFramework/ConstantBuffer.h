#ifndef CONSTANT_BUFFER_H
#define CONSTANT_BUFFER_H

#include <directxmath.h>
#include "SurfaceInfo.h"
#include "Light.h"

struct ConstantBuffer
{
	DirectX::XMMATRIX World;
	DirectX::XMMATRIX View;
	DirectX::XMMATRIX Projection;

	SurfaceInfo surface;

	Light light;

	DirectX::XMFLOAT3 EyePosW;
	float HasTexture;
};

#endif
