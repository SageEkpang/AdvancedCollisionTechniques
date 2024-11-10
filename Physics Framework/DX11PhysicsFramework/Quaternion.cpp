#include "Quaternion.h"

float Quaternion::QGetAngle(Quaternion4 q)
{
    return (float)(2 * acos(q.w));
}

Vector3 Quaternion::QGetAxis(Quaternion4 q)
{
    Vector3 v;
    float m;

    v = q.GetVector3();
    m = Vector::Magnitude(v);

    if (m <= MINTOL)
        return Vector3();
    else
        return v / m;
}

Quaternion4 Quaternion::QRotate(Quaternion4 q1, Quaternion4 q2)
{
    return q1 * q2 * (~q1);
}

Vector3 Quaternion::QVRotate(Quaternion4 q, Vector3 v)
{
    Quaternion4 t;
    t = q * v * (~q);
    return t.GetVector3();
}

float Quaternion::DegreesToRadians(float deg)
{
    return deg * PI / 180.0f;
}

float Quaternion::RadiansToDegrees(float rad)
{
    return rad * 180.0f / PI;
}

Quaternion4 Quaternion::MakeQFromEulerAngles(float x, float y, float z)
{
    Quaternion4     q;
    double     roll = DegreesToRadians(x);
    double     pitch = DegreesToRadians(y);
    double     yaw = DegreesToRadians(z);

    double     cyaw, cpitch, croll, syaw, spitch, sroll;
    double     cyawcpitch, syawspitch, cyawspitch, syawcpitch;

    cyaw = cos(0.5f * yaw);
    cpitch = cos(0.5f * pitch);
    croll = cos(0.5f * roll);
    syaw = sin(0.5f * yaw);
    spitch = sin(0.5f * pitch);
    sroll = sin(0.5f * roll);

    cyawcpitch = cyaw * cpitch;
    syawspitch = syaw * spitch;
    cyawspitch = cyaw * spitch;
    syawcpitch = syaw * cpitch;

    q.w = (float)(cyawcpitch * croll + syawspitch * sroll);
    q.x = (float)(cyawcpitch * sroll - syawspitch * croll);
    q.y = (float)(cyawspitch * croll + syawcpitch * sroll);
    q.z = (float)(syawcpitch * croll - cyawspitch * sroll);

    return q;
}

Vector3 Quaternion::MakeEulerAnglesFromQ(Quaternion4 q)
{
    double     r11, r21, r31, r32, r33, r12, r13;
    double     q00, q11, q22, q33;
    double     tmp;
    Vector3     u;

    q00 = q.w * q.w;
    q11 = q.x * q.x;
    q22 = q.y * q.y;
    q33 = q.z * q.z;

    r11 = q00 + q11 - q22 - q33;
    r21 = 2 * (q.x * q.y + q.w * q.z);
    r31 = 2 * (q.x * q.z - q.w * q.y);
    r32 = 2 * (q.y * q.z + q.w * q.x);
    r33 = q00 - q11 - q22 + q33;

    tmp = fabs(r31);
    if (tmp > 0.999999)
    {
        r12 = 2 * (q.x * q.y - q.w * q.z);
        r13 = 2 * (q.x * q.z + q.w * q.y);

        u.x = RadiansToDegrees(0.0f); //roll
        u.y = RadiansToDegrees((float)(-(PI / 2) * r31 / tmp));   // pitch
        u.z = RadiansToDegrees((float)atan2(-r12, -r31 * r13)); // yaw
        return u;
    }

    u.x = RadiansToDegrees((float)atan2(r32, r33)); // roll
    u.y = RadiansToDegrees((float)asin(-r31));      // pitch
    u.z = RadiansToDegrees((float)atan2(r21, r11)); // yaw
    return u;
}