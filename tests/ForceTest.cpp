#include <gtest/gtest.h>
#include "Force.h"

TEST(Force, userCtor)
{
  Force f1 = Force(ngl::Vec3{ 0,3,4 }, 5.0f);
  auto res1 = ngl::Vec3{ 0,3,4 };
  ASSERT_TRUE(f1.getForceValue() == res1);

  Force f2 = Force(ngl::Vec3{ 0,3,4 });
  auto res2 = ngl::Vec3{ 0,3,4 };
  ASSERT_TRUE(f2.getForceValue() == res2);
}

TEST(Force, opAdd)
{
  Force f1 = Force(ngl::Vec3{ 3.0f,0,0 });
  Force f2 = Force(ngl::Vec3{ 0,0,4.0f });
  ASSERT_TRUE((f1 + f2).getMagnitude() == 5.0f);
  Force f3 = f2;
  f3 += f1;
  ASSERT_TRUE(f3 == Force(ngl::Vec3{ 3.0f,0,4.0f }));
}

TEST(Force, opEq)
{
  Force f1 = Force(ngl::Vec3{ 1.0f,2.0f,3.0f });
  Force f2 = Force(ngl::Vec3{ 4.0f,5.0f,6.0f });
  f1 = f2;
  ngl::Vec3 res = f1.getForceValue();
  ASSERT_EQ(res.m_x, 4.0f);
  ASSERT_EQ(res.m_y, 5.0f);
  ASSERT_EQ(res.m_z, 6.0f);
}