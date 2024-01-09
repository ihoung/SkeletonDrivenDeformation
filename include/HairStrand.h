#ifndef HAIRSTRAND_H_
#define HAIRSTRAND_H_

#include <vector>
#include <memory>
#include <ngl/SimpleVAO.h>
#include <ngl/Mat4.h>
#include "Particle.hpp"

class HairStrand
{
public:
  HairStrand() = default;
  HairStrand(const HairStrand &) = default;
  HairStrand(size_t _numParticles, float _totalLength, float _damping=0.9f);
  void resetHairStrand();
  std::size_t getNumParticles() const;
  std::vector<Particle> &getParticles();
  float getSegmentLen() const;
  void setDamping(float _damping);
  float getDamping() const;
  void render(ngl::Mat4 _view, ngl::Mat4 _project) const;  
  void changeParticleNum(int);
  void changeLength(float);

  // test methods
//  Particle getPoint(int _index) const;
private:
  std::size_t m_numParticles;
  float m_length;
  float m_pDistance;
  std::vector<Particle> m_points;
  float m_damping;
  std::unique_ptr<ngl::AbstractVAO> m_vao;
  //std::vector<std::uint32_t> m_indexes;
};

#endif
