#pragma once

#include "Math.h"

class Camera
{
public:

    Camera();
    Camera(float fov, Vector3DF position = Vector3DF::Zero);
    
    float GetFov() const { return m_Fov; }

    void SetFov(float fov) 
    { 
        m_Fov = fov;
        UpdatePerspectiveMatrix();
        UpdateVPCacheMatrix();
    }

    const Vector3DF& GetPosition() const { return m_Position; }

    void SetPosition(const Vector3DF& position) 
    { 
        m_Position = position;
        UpdateViewMatrix();
        UpdateVPCacheMatrix(); 
    }
    
    const Matrix4x4 GetVPMatrix() const { return m_VPCacheMatrix; }

private:
    float m_Fov = 0;

    Vector3DF m_Position;

    Matrix4x4 m_ViewMatrix;
    Matrix4x4 m_PerspectiveMatrix;
    Matrix4x4 m_VPCacheMatrix;

    void UpdateViewMatrix();
    void UpdatePerspectiveMatrix();
    void UpdateVPCacheMatrix();
};