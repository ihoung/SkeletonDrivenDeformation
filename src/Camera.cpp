#include "Camera.h"
#include <ngl/Util.h>
#include <ngl/Quaternion.h>

Camera::Camera(ngl::Vec3 _eye, ngl::Vec3 _center, ngl::Vec3 _up, float _fovy, float _aspect, float _zNear, float _zFar) :
  m_eye{ _eye }, m_center{ _center }, m_up{ _up }, m_fovy{ _fovy }, m_aspect{ _aspect }, m_zNear{ _zNear }, m_zFar{ _zFar }
{
  m_up.normalize();
  m_view = ngl::lookAt(m_eye, m_center, m_up);
  m_project = ngl::perspective(m_fovy, m_aspect, m_zNear, m_zFar);
  m_rot.identity();
}

void Camera::updateViewMat()
{
	ngl::Mat4 identity;
	if (m_rot == identity)
	{
		m_view = ngl::lookAt(m_eye, m_center, m_up);
		return;
	}

	auto mat = m_rot;
	mat.transpose();
	m_view = mat * m_view;
	m_up = m_view.getUpVector();
	ngl::Vec3 forward = m_view.getForwardVector();
	forward.normalize();
	m_eye = m_center + (m_eye - m_center).length() * forward;
}

ngl::Mat4 Camera::getViewMat() const
{
  return m_view;
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

void Camera::translateCamereAlongEye(float _diff)
{
	ngl::Vec3 look = m_center - m_eye;
	look.normalize();
	m_center += _diff * look;
	m_eye += _diff * look;
	updateViewMat();
}

void Camera::rotCamera(ngl::Vec2 _diff)
{
	ngl::Vec3 right = (m_center - m_eye).cross(m_up);
	ngl::Vec3 up = m_up;
	right.normalize();
	up.normalize();
	ngl::Vec3 turn = right * _diff.m_x + up * _diff.m_y;
	ngl::Vec3 back = m_eye - m_center;
	ngl::Vec3 axis = back.cross(turn);
	axis.normalize();
	ngl::Quaternion q;
	q.fromAxisAngle(axis, _diff.length());
	m_rot = q.toMat4();
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
  m_view = ngl::lookAt(m_eye, m_center, m_up);
  m_project = ngl::perspective(m_fovy, m_aspect, m_zNear, m_zFar);
  m_rot.identity();
}

ngl::Vec3 Camera::getPosition() const
{
	return m_center;
}
