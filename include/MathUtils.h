#pragma once
#include <ngl/Quaternion.h>

class MathUtils
{
public:
	static ngl::Quaternion QuaternionFromTwoVectors(ngl::Vec3 _from, ngl::Vec3 _to);
};