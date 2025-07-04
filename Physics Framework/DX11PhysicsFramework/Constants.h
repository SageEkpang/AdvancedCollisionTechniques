#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Structures.h"

constexpr int MAX_X = 20;
constexpr int MIN_X = -20;

constexpr int MAX_Z = 20;
constexpr int MIN_Z = -20;

// WINDOW DEFINE(s)
#define FPS60 1.0f/60.0f
#define MINTOL 0.0001


// MATHS SYMBOLS
#define PI 3.14159
#define EPSILON 0.00000286389039184749
#define SIGMA 200
#define INFINITE_MASS 0.0f


// INPUT DEFINE(s)
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_9 0x38

#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44

#define VK_Q 0x51
#define VK_F 0x46
#define VK_E 0x45
#define VK_I 0x49

#define VK_C 0x43
#define VK_Z 0x5A
#define VK_X 0x58
#define VK_R 0x52

#define VK_V 0x56
#define VK_Y 0x59


// INPUT DEFINE(s) (Special Keys)
#define VK_TAB 0x09
#define VK_RETURN 0x0D
#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_BACK 0x08

#define VK_ADD 0x6B
#define VK_SUBTRACT 0x6D


// MATERIAL DEFINE(s)
#define MATERIAL_SHINY Material(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f))
#define MATERIAL_ROUGH

#define MATERIAL_MAX Material(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f))
#define MATERIAL_FLAT Material(XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f))
#define MATERIAL_WIREFRAME Material(XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f))
#define MATERIAL_GROUND Material(XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f))

// INERTIA TENSOR DEFINE(s)


// GRAVITY DEFINE(s)
#define GRAVITY_EARTH 9.81f
#define GRAVITY_MARS 3.7f
#define GRAVITY_SATURN 10.5f
#define GRAVITY_SUN 293.0f
#define GRAVITY_MERCURY 3.7f
#define GRAVITY_URANUS 9.0f


// RESTITUTION COEFFICIENT DEFINE(s)
#define RESTCCOEF_SILICON 1.79
#define RESTCCOEF_ALUMINA 1.24
#define RESTCCOEF_STAINLESS_STEEL 1.0
#define RESTCCOEF_TUNGSTEN 0.37
#define RESTCCOEF_LEAD 0.08
#define RESTCCOEF_ALUMINUM 0.1
#define RESTCCOEF_COPPER 0.15
#define RESTCCOEF_NICKEL 0.15
#define RESTCCOEF_ZINC 0.21


// FRICTION COEFFICIENT DEFINE(s)
#define FRICCOEF_GRAPHIRE 0.1
#define FRICCOEF_PHOSPHOR_BRONZE 0.35
#define FRICCOEF_CAST_IRON 0.4
#define FRICCOEF_ACRYLIC 0.5
#define FRICCOEF_COPPER 0.53
#define FRICCOEF_BRASS 0.51
#define FRICCOEF_ALUMINUM 0.61
#define FRICCOEF_GLASS 0.9
#define FRICCOEF_DIAMOND 0.1




#endif
