#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <iostream>

NGLScene::NGLScene(QWidget *_parent) :QOpenGLWidget(_parent)
{
  setFocusPolicy(Qt::StrongFocus);
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}

const std::string DEFAULT_MESH_FILE = "resources/cylinder.obj";

const auto MeshShader ="MeshShader";

void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::initialize();
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  // initialize main camera
  m_mainCamera = std::make_unique<Camera>(CAMERA_EYE, CAMERA_CENTER, CAMERA_UP);

  ngl::ShaderLib::loadShader(MeshShader, "shaders/MeshVertex.glsl", "shaders/MeshFragment.glsl");
  startTimer(10);

  m_strand = std::make_shared<HairStrand>(10, 5.0f);
  m_simulator = std::make_unique<Simulator>(m_strand);

  m_mesh = std::make_unique<Mesh>(DEFAULT_MESH_FILE);
}


void NGLScene::paintGL()
{
  //if (m_isSimulationOn)
  //  m_simulator->update();

  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);

  //m_strand->render(m_mainCamera->getViewMat(), m_mainCamera->getProjectMat());
  m_mesh->drawSolid(m_mainCamera->getViewMat(), m_mainCamera->getProjectMat(), MeshShader);
  m_mesh->drawWire(m_mainCamera->getViewMat(), m_mainCamera->getProjectMat(), MeshShader);
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{ 
  //QOpenGLWidget::keyPressEvent(_event);
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
    m_win.spinXFace=0;
    m_win.spinYFace=0;
    m_modelPos.set(ngl::Vec3::zero());
    break;
  case Qt::Key_Alt:
    m_win.camera_mode = true;
    break;
  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}

void NGLScene::keyReleaseEvent(QKeyEvent *_event) 
{
  switch (_event->key())
  {
  case Qt::Key_Alt:
    m_win.camera_mode = false;
    break;

  default:
    break;
  }

    update();
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
   update();
}

void NGLScene::resetCamera()
{
  m_mainCamera->setCamera(CAMERA_EYE, CAMERA_CENTER, CAMERA_UP);
  update();
}

void NGLScene::changeHairPrecision(int _value)
{
  m_strand->changeParticleNum(_value);
  update();
}

void NGLScene::changeHairLength(int _value)
{
  m_strand->changeLength((float)_value/50.0f);
  update();
}

void NGLScene::changeHairDamping(int _value)
{
  m_strand->setDamping((float)_value / 10.0f);
  update();
}

void NGLScene::changeTimeStep(double _timeStep)
{
  m_simulator->setTimeStep((float)_timeStep);
  update();
}

void NGLScene::changeStimulationStatus(int _status)
{
  if(_status == 2)
    m_isSimulationOn = true;
  else
    m_isSimulationOn = false;

  if (!m_isSimulationOn)
    m_strand->resetHairStrand();
  update();
}

void NGLScene::changeWindDirX(double _dirX)
{
  m_windDirCache.m_x = (float)_dirX;
}

void NGLScene::changeWindDirY(double _dirY)
{
  m_windDirCache.m_y = (float)_dirY;
}

void NGLScene::changeWindDirZ(double _dirZ)
{
  m_windDirCache.m_z = (float)_dirZ;
}

void NGLScene::applyWindDirChanged()
{
  m_curWindDir = m_windDirCache;
  m_simulator->clearForce();
  m_simulator->addForce(Force(m_curWindDir, m_windForce));
  update();
}

void NGLScene::changeWindForce(int _value)
{
  m_windForce = (float)_value;
  m_simulator->clearForce();
  m_simulator->addForce(Force(m_curWindDir, m_windForce));
  update();
}

