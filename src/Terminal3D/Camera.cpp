#include "Terminal3D/Camera.h"

Camera::Camera() : m_Fov(60) 
{
    UpdateViewMatrix();
    UpdatePerspectiveMatrix();
    UpdateVPCacheMatrix();
}

Camera::Camera(float fov) : m_Fov(fov)
{
    UpdateViewMatrix();
    UpdatePerspectiveMatrix();
    UpdateVPCacheMatrix();
}

void Camera::SetPosition(Vector3DF val)
{
    GameObject::SetPosition(val);
    UpdateViewMatrix();
    UpdateVPCacheMatrix();
}

void Camera::SetRotation(QuaternionF val)
{
    GameObject::SetRotation(val);
    UpdateViewMatrix();
    UpdateVPCacheMatrix();
}

void Camera::UpdateViewMatrix()
{   
    m_ViewMatrix = GetTransformationMatrix();
}

void Camera::UpdatePerspectiveMatrix()
{
    float S = 1.f / (std::tan(m_Fov * PI / 360.f));

    auto& p = m_PerspectiveMatrix.m;

    float n = 0.5f;
    float f = 25.f;
    
    p[0][0] = S;
    p[1][1] = S;
    p[2][2] = -f / (f - n);
    p[3][2] = -f * n / (f - n);
    p[2][3] = -1;
}

void Camera::UpdateVPCacheMatrix()
{
    m_VPCacheMatrix = m_PerspectiveMatrix * m_ViewMatrix;
}
