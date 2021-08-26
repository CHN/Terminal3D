#pragma once

#include "Math.h"
#include "GameObject.h"

class Camera : public GameObject
{
public:

    Camera();
    Camera(float fov);
    
    float GetFov() const { return m_Fov; }

    void SetFov(float fov) 
    { 
        m_Fov = fov;
        UpdatePerspectiveMatrix();
        UpdateVPCacheMatrix();
    }
    
    const Matrix4x4 GetVPMatrix() const { return m_VPCacheMatrix; }


    void SetPosition(Vector3DF val) override;
    void SetRotation(QuaternionF val) override;

private:
    float m_Fov = 0;

    Matrix4x4 m_ViewMatrix;
    Matrix4x4 m_PerspectiveMatrix;
    Matrix4x4 m_VPCacheMatrix;

    void UpdateViewMatrix();
    void UpdatePerspectiveMatrix();
    void UpdateVPCacheMatrix();
};