#include "Camera.h"
#include <ngl/Util.h>

Camera::Camera(ngl::Vec3 _eye, ngl::Vec3 _center, ngl::Vec3 _up, float _fovy, float _aspect, float _zNear, float _zFar) :
  m_eye{ _eye }, m_center{ _center }, m_up{ _up }, m_fovy{ _fovy }, m_aspect{ _aspect }, m_zNear{ _zNear }, m_zFar{ _zFar }
{
  m_up.normalize();
  updateViewMat();
  m_project = ngl::perspective(m_fovy, m_aspect, m_zNear, m_zFar);
  m_rot.identity();
}

void Camera::updateViewMat()
{
  m_view = ngl::lookAt(m_eye, m_center, m_up);
}

ngl::Mat4 Camera::getViewMat() const
{
  auto mat = m_rot;
  mat.transpose();
  return mat * m_view;
}

ngl::Mat4 Camera::getProjectMat() const
{
  return m_project;
}

void Camera::translateCamera(ngl::Vec2 _diff)
{
  ngl::Vec3 right = (m_eye - m_center).cross(m_up);
  right.normalize();
  auto translation = _diff.m_x * right + _diff.m_y * m_up;
  m_eye += translation;
  m_center += translation;
  updateViewMat();
}

void Camera::rotCamera(ngl::Vec2 _diff)
{
  ngl::Mat4 rotX, rotY;
  rotX.rotateX(_diff.m_x);
  rotY.rotateY(_diff.m_y);
  m_rot *= rotX * rotY;
}

void Camera::setCamera(ngl::Vec3 _eye, ngl::Vec3 _center, ngl::Vec3 _up, float _fovy, float _aspect, float _zNear, float _zFar)
{
  m_eye = _eye;
  m_center = _center;
  m_up = _up;
  m_up.normalize();
  m_fovy = _fovy;
  m_aspect = _aspect;
  m_zNear = _zNear;
  m_zFar = _zFar;
  updateViewMat();
  m_project = ngl::perspective(m_fovy, m_aspect, m_zNear, m_zFar);
  m_rot.identity();
}