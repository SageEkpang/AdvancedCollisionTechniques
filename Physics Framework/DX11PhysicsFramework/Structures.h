#ifndef STRUCTURES_H
#define STRUCTURES_H

// NOTE: LIBRARY INCLUDE(s)
#include <windows.h>
#include <cstring>
#include <d3d11.h>
#include <directxmath.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxcolors.h>
#include "DDSTextureLoader.h"
#include "resource.h"

// NOTE: GUI INCLUDE(s)
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"


// PHYSICS DATA(s)

enum MaterialTypes
{
	MATERIAL_SILICON,
	MATERIAL_ALUMINA,
	MATERIAL_STAINLESS_STEEL,
	MATERIAL_TUNGSTEN,
	MATERIAL_ALUMINUM,
	MATERIAL_COPPER,
	MATERIAL_NICKEL,
	MATERIAL_ZINC
};

enum DragShapeTypes
{
	DRAG_SPHERE,
	DRAG_HALF_SPHERE,
	DRAG_CONE,
	DRAG_CUBE,
	DRAG_ANGLED_CUBE,
	DRAG_LONG_CYLINDER,
	DRAG_SHORT_CYLINDER,
	DRAG_STREAMLINED_BODY,
	DRAG_STREAMLINED_HALF_BODY
};

enum PhysicTag
{
	NONE,
	PHYSICS_STATIC,
	PHYSICS_DYNAMIC,
	PHYSICS_KINEMATIC
};

enum ColliderType
{
	COLLIDER_NONE,
	COLLIDER_BOX,
	COLLIDER_PLANE,
	COLLIDER_SPHERE,
	COLLIDER_OBB,
	COLLIDER_MESH
};

#endif