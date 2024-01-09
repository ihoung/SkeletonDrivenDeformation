#include "Simulator.h"

Simulator::Simulator(std::shared_ptr<HairStrand> strand, float _timeStep) :m_strand{ strand }, m_externalForce{ Force({0.0f,0.0f,0.0f}) }, m_timeStep{ _timeStep }
{

}

void Simulator::addForce(const Force &_f)
{
  m_externalForce += _f;
  updateIntegratedForce();
}

void Simulator::addForce(const ngl::Vec3 &_vec)
{
  m_externalForce += Force(_vec);
  updateIntegratedForce();
}

void Simulator::clearForce()
{
  m_externalForce = Force({ 0.0f,0.0f,0.0f });
  updateIntegratedForce();
}

void Simulator::setTimeStep(float _timeStep)
{
  m_timeStep = _timeStep;
}

void Simulator::updateIntegratedForce()
{
  m_integratedForce = m_externalForce + GRAVITY;
}

// This part is implementation of Follow The Leader (FLT) algorithm mentioned in paper
// Fast Simulation of Inextensible Hair and Fur, by M. Müller et al. 2012
void Simulator::update()
{
  std::vector<Particle> &particles = m_strand->getParticles();
  std::size_t numP = m_strand->getNumParticles();
  float pDistance = m_strand->getSegmentLen();
  float damping = m_strand->getDamping();

  for (std::size_t i = numP - 1; i >= 1; i--)
  {
    particles[i].oldPos = particles[i].pos;

    // calculate new position
    particles[i].pos = particles[i].oldPos + m_timeStep * particles[i].velocity + m_timeStep * m_timeStep * m_integratedForce.getForceValue();

    // start to solve constraint
    Particle &pre = particles[i - 1];

    auto direction = particles[i].pos - pre.pos;
    direction.normalize();

    ngl::Vec3 pTemp = particles[i].pos;

    // constraint the new position of particle within fixed distance from the previous particle
    particles[i].pos = pre.pos + direction * pDistance;
    // end solving constraint

    // update velocity, position & force
    particles[i].velocity = ((particles[i].pos - particles[i].oldPos) / m_timeStep);

    // correct the velocity with the correction vector computed for previous particle
    particles[i].velocity += (i + 1 >= numP) ? ngl::Vec3(0, 0, 0) : damping * (-particles[i + 1].correction / m_timeStep);
    particles[i].correction = particles[i].pos - pTemp;
  }
}