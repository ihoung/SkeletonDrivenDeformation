#include <memory>
#include "HairStrand.h"
#include "Force.h"

class Simulator
{
public :
  Simulator(std::shared_ptr<HairStrand> strand, float _timeStep = 1.0f / 125.0f);
  void update();
  void addForce(const Force &);
  void addForce(const ngl::Vec3 &);
  void clearForce();
  void setTimeStep(float _timeStep);
private:
  std::shared_ptr<HairStrand> m_strand;
  Force m_externalForce;
  Force m_integratedForce;
  float m_timeStep;
  const Force GRAVITY = Force({ 0.0f,-1.0f, 0.0f }, 9.8);
  void updateIntegratedForce();
};