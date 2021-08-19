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
	const auto p = m_Position * -1.f;
	auto q = m_Rotation;

	//q.Inverse();

	MatrixF4x4 rm;

	rm.m[0][0] = 1.f - 2.f * q.y * q.y - 2.f * q.z * q.z;
	rm.m[0][1] = 2.f * q.x * q.y - 2.f * q.z * q.w;
	rm.m[0][2] = 2.f * q.x * q.z + 2.f * q.y * q.w;
	rm.m[0][3] = 0;

	rm.m[1][0] = 2.f * q.x * q.y + 2.f * q.z * q.w;
	rm.m[1][1] = 1.f - 2.f * q.x * q.x - 2.f * q.z * q.z;
	rm.m[1][2] = 2.f * q.y * q.z - 2.f * q.x * q.w;
	rm.m[1][3] = 0;

	rm.m[2][0] = 2.f * q.x * q.z - 2.f * q.y * q.w;
	rm.m[2][1] = 2.f * q.y * q.z + 2.f * q.x * q.w;
	rm.m[2][2] = 1.f - 2.f * q.x * q.x - 2.f * q.y * q.y;
	rm.m[2][3] = 0;

	rm.m[3][0] = 0;
	rm.m[3][1] = 0;
	rm.m[3][2] = 0;
	rm.m[3][3] = 1;

	MatrixF4x4 pm;

	pm.m[0][0] = 1;   pm.m[0][1] = 0;   pm.m[0][2] = 0;   pm.m[0][3] = p.x;
	pm.m[1][0] = 0;   pm.m[1][1] = 1;   pm.m[1][2] = 0;   pm.m[1][3] = p.y;
	pm.m[2][0] = 0;   pm.m[2][1] = 0;   pm.m[2][2] = 1;   pm.m[2][3] = p.z;
	pm.m[3][0] = 0;   pm.m[3][1] = 0;   pm.m[3][2] = 0;   pm.m[3][3] = 1;

	m_ViewMatrix = rm * pm;
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
