#include <ngl/Vec3.h>

class Force 
{
public:
  Force() = default;
  Force(const Force &) = default;
  Force(ngl::Vec3 _dir, float _magn);
  Force(ngl::Vec3 _value);
  ngl::Vec3 getForceValue() const;
  ngl::Vec3 getDirection() const;
  float getMagnitude() const;
  Force operator+(const Force &) const;
  bool operator==(const Force &) const;
  Force &operator+=(const Force &);
  Force &operator=(const Force &);
private:
  ngl::Vec3 m_dir;
  float m_magn;
};
