#ifndef CAMERA_H_
#define CAMERA_H_

#include <ngl/Vec2.h>
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>

class Camera
{
public:
  Camera() = default;
  Camera(const Camera &) = default;
  Camera(ngl::Vec3 _eye, ngl::Vec3 _center, ngl::Vec3 _up, float _fovy = 45.0f, float _aspect = 1.0f, float _zNear = 0.1f, float _zFar = 200.0f);
  ngl::Mat4 getViewMat() const;
  ngl::Mat4 getProjectMat() const;
  void translateCamera(ngl::Vec2);
  void translateCamereAlongEye(float);
  void rotCamera(ngl::Vec2);
  void setCamera(ngl::Vec3 _eye, ngl::Vec3 _center, ngl::Vec3 _up, float _fovy = 45.0f, float _aspect = 1.0f, float _zNear = 0.1f, float _zFar = 200.0f);
  ngl::Vec3 getPosition() const;
private:
  ngl::Vec3 m_eye;
  ngl::Vec3 m_center;
  ngl::Vec3 m_up;

  float m_fovy;
  float m_aspect;
  float m_zNear;
  float m_zFar;

  ngl::Mat4 m_view;
  ngl::Mat4 m_project;
  ngl::Mat4 m_rot;

  void updateViewMat();
};

#endif
