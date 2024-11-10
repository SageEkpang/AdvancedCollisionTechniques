#pragma once
#ifndef QUATERNION_H
#define QUATERNION_H

#include "Constants.h"
#include "Structures.h"
#include "Vector.h"

class Quaternion
{
public:

    static float QGetAngle(Quaternion4 q);
    static Vector3 QGetAxis(Quaternion4 q);

    static Quaternion4 QRotate(Quaternion4 q1, Quaternion4 q2);
    static Vector3 QVRotate(Quaternion4 q, Vector3 v);

    static float DegreesToRadians(float deg);
    static float RadiansToDegrees(float rad);

    static Quaternion4 MakeQFromEulerAngles(float x, float y, float z);
    static Vector3 MakeEulerAnglesFromQ(Quaternion4 q);
};

#endif
