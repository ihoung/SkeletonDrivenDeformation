#include "MathUtils.h"

ngl::Quaternion MathUtils::QuaternionFromTwoVectors(ngl::Vec3 _from, ngl::Vec3 _to)
{
    ngl::Vec3 v = _to.cross(_from);
    float _s = sqrt(powf(_from.length(), 2) * powf(_to.length(), 2)) + _from.dot(_to);
    return ngl::Quaternion(_s, v.m_x, v.m_y, v.m_z);
}
