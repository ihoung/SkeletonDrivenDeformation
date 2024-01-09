#include "HairStrand.h"
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Util.h>
#include <ngl/VAOFactory.h>

HairStrand::HairStrand(std::size_t _numParticles, float totalLength, float _damping) :m_numParticles{ _numParticles }, m_length{ totalLength }, m_damping{ _damping }
{
  resetHairStrand();
  m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_LINE_STRIP);
}

std::size_t HairStrand::getNumParticles() const
{
  return m_numParticles;
}

std::vector<Particle> &HairStrand::getParticles()
{
  return m_points;
}

float HairStrand::getSegmentLen() const
{
  return m_pDistance;
}

void HairStrand::setDamping(float _damping)
{
  m_damping = _damping;
}

float HairStrand::getDamping() const
{
  return m_damping;
}

void HairStrand::render(ngl::Mat4 _view, ngl::Mat4 _project) const
{
  ngl::ShaderLib::setUniform("MVP", _project * _view);
  glPointSize(3);
  m_vao->bind();
  m_vao->setData(ngl::SimpleVAO::VertexData(m_numParticles * sizeof(Particle), m_points[0].pos.m_x));
  m_vao->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(Particle), 0);
  m_vao->setNumIndices(m_numParticles);
  glEnable(GL_PROGRAM_POINT_SIZE);
  m_vao->draw();
  glDisable(GL_PROGRAM_POINT_SIZE);
  m_vao->unbind();
}

//Particle HairStrand::getPoint(int _index) const
//{
//  return m_points[_index];
//}

void HairStrand::changeParticleNum(int _num)
{
  m_numParticles = _num;
  resetHairStrand();
}

void HairStrand::changeLength(float _length)
{
  m_length = _length;
  resetHairStrand();
}

void HairStrand::resetHairStrand()
{
  m_points.resize(m_numParticles);
  float curPosY = 3.0f;
  m_pDistance = m_length / (float)(m_numParticles - 1);
  for (std::uint32_t i = 0; i < m_numParticles; ++i)
  {
    m_points[i]=Particle({ 0, curPosY, 0 });
    curPosY -= m_pDistance;

  }
}
