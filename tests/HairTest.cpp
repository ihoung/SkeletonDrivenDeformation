#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include <ngl/Vec3.h>
#include "HairStrand.h"
#include "Camera.h"

TEST(HairStrand, render)
{
//  HairStrand strand = HairStrand(10,5.0f);
//  auto p = strand.getPoint(2);
//  ASSERT_EQ(p.pos.m_y, 2.0f);
}

TEST(HairStrand, transformParticle)
{
  HairStrand strand = HairStrand(11, 5.0f);
  auto particles = strand.getParticles();
  ASSERT_EQ(particles[10].pos.m_y, -2.0f);
  particles[10].pos += ngl::Vec3{ 1.0f,0.0f,1.0f };
  ASSERT_TRUE(particles[10].pos == (ngl::Vec3{ 1.0f,-2.0f,1.0f }));
}

