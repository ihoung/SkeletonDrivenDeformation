#include <gtest/gtest.h>
#include "MathUtils.h"
#include <ngl/Util.h>
#include <iostream>

TEST(MathUtils, quaternionFromTwoVectors)
{
	ngl::Vec3 v1{ 0,1,0 };
	ngl::Vec3 v2{ 0,0,1 };
	ngl::Quaternion q = MathUtils::QuaternionFromTwoVectors(v1, v2);
	ngl::Vec3 v3{ 1,0,0 };
	ngl::Vec4 v4 = q * ngl::Vec4(v3, 0);
	v4.normalize();
	ASSERT_EQ(v4, ngl::Vec4({ 1,0,0,0 }));
	v3 = ngl::Vec3{ 0.0f, sinf(ngl::radians(45)), -cosf(ngl::radians(45)) };
	v4 = q * ngl::Vec4(v3, 0);
	v4.normalize();
	ASSERT_EQ(v4, ngl::Vec4({ 0.0f, sinf(ngl::radians(45)), cosf(ngl::radians(45)), 0.0f }));
}