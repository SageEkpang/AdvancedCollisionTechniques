#ifndef SURFACE_INFO_H
#define SURFACE_INFO_H

#include <directxmath.h>

struct SurfaceInfo
{
	DirectX::XMFLOAT4 AmbientMtrl;
	DirectX::XMFLOAT4 DiffuseMtrl;
	DirectX::XMFLOAT4 SpecularMtrl;
};

#endif