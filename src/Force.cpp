#include "Force.h"

Force::Force(ngl::Vec3 _dir, float _magn) :m_dir{ _dir }, m_magn{ _magn }
{
  if (m_dir.length() != 0.0f)
	m_dir.normalize();
}

Force::Force(ngl::Vec3 _value)
{
  m_magn = _value.length();
  m_dir = _value;
  if (m_magn != 0.0f)
	m_dir.normalize();
}

Force Force::operator+(const Force &rhs) const
{
  return Force(this->m_dir * this->m_magn + rhs.m_dir * rhs.m_magn);
}

bool Force::operator==(const Force &rhs) const
{
  return this->m_dir == rhs.m_dir && this->m_magn == rhs.m_magn;
}

Force &Force::operator+=(const Force &rhs)
{
  auto v = m_dir * m_magn + rhs.m_dir * rhs.m_magn;
  m_magn = v.length();
  m_dir = v;
  if (m_magn != 0.0f)
	m_dir.normalize();
  return *this;
}

Force &Force::operator=(const Force &rhs)
{
  m_dir = rhs.m_dir;
  m_magn = rhs.m_magn;
  return *this;
}

float Force::getMagnitude() const
{
  return m_magn;
}

ngl::Vec3 Force::getDirection() const
{
  return m_dir;
}

ngl::Vec3 Force::getForceValue() const
{
  return m_dir * m_magn;
}
