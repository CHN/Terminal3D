#include "Terminal3D/GameObject.h"

void GameObject::UpdateTransformationMatrixCache()
{
	auto p = m_Position;
	auto s = m_Scale;
	auto q = m_Rotation;

	MatrixF4x4 sm;

	sm.m[0][0] = s.x; sm.m[0][1] = 0;   sm.m[0][2] = 0;   sm.m[0][3] = 0;
	sm.m[1][0] = 0;   sm.m[1][1] = s.y; sm.m[1][2] = 0;   sm.m[1][3] = 0;
	sm.m[2][0] = 0;   sm.m[2][1] = 0;   sm.m[2][2] = s.z; sm.m[2][3] = 0;
	sm.m[3][0] = 0;   sm.m[3][1] = 0;   sm.m[3][2] = 0;   sm.m[3][3] = 1;

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

	m_TransformationMatrixCache = pm * rm * sm;
}

