#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <d3d11.h>

struct Geometry
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int numberOfIndices;

	UINT vertexBufferStride;
	UINT vertexBufferOffset;
};

#endif