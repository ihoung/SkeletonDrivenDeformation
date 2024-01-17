#include "Camera.h"
#include <ngl/Util.h>
#include <ngl/Quaternion.h>
#include <iostream>

Camera::Camera(ngl::Vec3 _eye, ngl::Vec3 _center, ngl::Vec3 _up, float _fovy, float _aspect, float _zNear, float _zFar) :
  m_eye{ _eye }, m_center{ _center }, m_up{ _up }, m_fovy{ _fovy }, m_aspect{ _aspect }, m_zNear{ _zNear }, m_zFar{ _zFar }
{
  m_up.normalize();
  updateViewMat();
  m_project = ngl::perspective(m_fovy, m_aspect, m_zNear, m_zFar);
}

void Camera::updateViewMat()
{
	m_view = ngl::lookAt(m_eye, m_center, m_up);
}

ngl::Mat4 Camera::getViewMat() const
{
  return m_view;
}

ngl::Mat4 Camera::getProjectMat() const
{
  return m_project;
}

void Camera::translateAlongViewPanel(ngl::Vec2 _diff)
{
  ngl::Vec3 right = (m_eye - m_center).cross(m_up);
  right.normalize();
  auto translation = _diff.m_x * right + _diff.m_y * m_up;
  m_eye += translation;
  m_center += translation;
  updateViewMat();
}

void Camera::translateForwardBack(float _diff)
{
	ngl::Vec3 look = m_center - m_eye;
	look.normalize();
	m_center += _diff * look;
	m_eye += _diff * look;
	updateViewMat();
}

void Camera::rotAroundEye(ngl::Vec2 _diff)
{
	float angle = _diff.length();
	ngl::Vec3 forward = m_eye - m_center;
	float radius = forward.length();
	forward.normalize();
	ngl::Vec3 up = m_up;
	up.normalize();
	ngl::Vec3 right = -forward.cross(up);
	right.normalize();
	ngl::Vec3 v = right * _diff.m_x + up * _diff.m_y;
	v.normalize();
	ngl::Vec3 axis = -v.cross(forward);
	ngl::Quaternion q;
	q.fromAxisAngle(axis, angle);
	q.normalise();
	ngl::Vec4 _temp = q * ngl::Vec4(forward, 0.0f);
	m_center = m_eye - _temp.toVec3() * radius;
	_temp = q * ngl::Vec4(up, 0.0f);
	m_up = _temp.toVec3();

	updateViewMat();
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
}

ngl::Vec3 Camera::getPosition() const
{
	return m_center;
}

ngl::Vec3 Camera::getUpVector() const
{
	return m_up;
}
