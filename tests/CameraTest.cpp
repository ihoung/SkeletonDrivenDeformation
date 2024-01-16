#include <gtest/gtest.h>
#include <ngl/Mat4.h>
#include "Camera.h"
#include <ngl/Quaternion.h>

TEST(Camera, userCtor)
{
  //Camera c = Camera({ 0,0,10 }, { 0,0,0 }, { 0,1,0 });
  //ngl::Mat4 vp = c.getVPMat();
  //ngl::Mat4 res = ngl::lookAt({ 0,0,10 }, { 0,0,0 }, { 0,1,0 }) * ngl::perspective(45.0f, 1.0f, 0.1f, 200.0f);
  //ASSERT_EQ(vp, res);
}

TEST(Camera, rotateCamera)
{
	//Camera c = Camera({ 0,0,10 }, { 0,0,0 }, { 0,1,0 });
	ngl::Quaternion q{};
	ngl::Mat4 mat;
	ASSERT_EQ(q.toMat4(), mat);
}
