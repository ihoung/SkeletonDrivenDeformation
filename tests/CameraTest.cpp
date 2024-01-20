#include <gtest/gtest.h>
#include <ngl/Util.h>
#include <memory>
#include <iostream>
#include "Camera.h"


TEST(Camera, rotateCamera)
{
	Camera camera(ngl::Vec3{ 0.0f,0.0f,10.0f }, ngl::Vec3{ 0.0f,0.0f,0.0f }, ngl::Vec3{ 0.0f,1.0f,0.0f });
	camera.rotAroundEye(ngl::Vec2{ 0.0f, 90.0f });
	ngl::Vec3 pos = camera.getPosition();
	ASSERT_EQ(camera.getPosition(), ngl::Vec3({ 0.0f,10.0f,10.0f }));
}
