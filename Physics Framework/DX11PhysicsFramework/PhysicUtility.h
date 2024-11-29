#pragma once
#ifndef PHYSIC_UTILITY_H
#define PHYSIC_UTILITY_H

#include "Constants.h"
#include "Structures.h"

namespace PhysicUtility
{
	namespace MeshHelper
	{
		// void SetMeshAndGeometry(Geometry geometry, MeshData meshData, char* fileName, ID3D11Device* device);
	}

	namespace TextureHelper
	{
		// 
		void SetTexture(ID3D11ShaderResourceView* texture, const wchar_t* fileName, ID3D11Device* device);
	}





};

#endif
