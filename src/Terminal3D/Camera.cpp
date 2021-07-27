#include "Terminal3D/Camera.h"

Camera::Camera() : m_Fov(60) 
{
    UpdateViewMatrix();
    UpdatePerspectiveMatrix();
    UpdateVPCacheMatrix();
}

Camera::Camera(float fov, Vector3DF position) : m_Fov(fov), m_Position(position) 
{
    UpdateViewMatrix();
    UpdatePerspectiveMatrix();
    UpdateVPCacheMatrix();
}

void Camera::UpdateViewMatrix()
{   
    Matrix4x4 transformMatrix;

    float pos[] = { m_Position.x, m_Position.y, m_Position.z, 1 };

    transformMatrix.SetColumns(3, pos);

    m_ViewMatrix = transformMatrix.Inverse();
}

void Camera::UpdatePerspectiveMatrix()
{
    float S = 1.f / (std::tan(m_Fov * M_PI / 360.f));

    auto& p = m_PerspectiveMatrix.m;

    float n = 0.5f;
    float f = 20.f;
    
    p[0][0] = S;
    p[1][1] = S;
    p[2][2] = -f / (f - n);
    p[3][2] = -f * n / (f - n);
    p[2][3] = -1;
}

void Camera::UpdateVPCacheMatrix()
{
    m_VPCacheMatrix = m_PerspectiveMatrix;
}
