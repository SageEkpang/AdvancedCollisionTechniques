#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <d3d11.h>

struct MeshData
{
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	UINT VBStride;
	UINT VBOffset;
	UINT IndexCount;
};

#endif
