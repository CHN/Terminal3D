#include "MatrixTRSOperations.h"

template MatrixTRSOperations<float>;
template MatrixTRSOperations<double>;

template<typename T>
Matrix<T, 4, 4> MatrixTRSOperations<T>::GetPositionMatrix(const Vector3D<T>& position)
{
	Matrix<T, 4, 4> matrix;

	matrix.m[0][0] = 1; matrix.m[0][1] = 0; matrix.m[0][2] = 0; matrix.m[0][3] = position.x;
	matrix.m[1][0] = 0; matrix.m[1][1] = 1; matrix.m[1][2] = 0; matrix.m[1][3] = position.y;
	matrix.m[2][0] = 0; matrix.m[2][1] = 0; matrix.m[2][2] = 1; matrix.m[2][3] = position.z;
	matrix.m[3][0] = 0; matrix.m[3][1] = 0; matrix.m[3][2] = 0; matrix.m[3][3] = 1;

	return matrix;
}

template<typename T>
Matrix<T, 4, 4> MatrixTRSOperations<T>::GetRotationMatrix(const Quaternion<T>& r /*rotation*/)
{
	Matrix<T, 4, 4> matrix;

	matrix.m[0][0] = 1.f - 2.f * r.y * r.y - 2.f * r.z * r.z;
	matrix.m[0][1] = 2.f * r.x * r.y - 2.f * r.z * r.w;
	matrix.m[0][2] = 2.f * r.x * r.z + 2.f * r.y * r.w;
	matrix.m[0][3] = 0;

	matrix.m[1][0] = 2.f * r.x * r.y + 2.f * r.z * r.w;
	matrix.m[1][1] = 1.f - 2.f * r.x * r.x - 2.f * r.z * r.z;
	matrix.m[1][2] = 2.f * r.y * r.z - 2.f * r.x * r.w;
	matrix.m[1][3] = 0;

	matrix.m[2][0] = 2.f * r.x * r.z - 2.f * r.y * r.w;
	matrix.m[2][1] = 2.f * r.y * r.z + 2.f * r.x * r.w;
	matrix.m[2][2] = 1.f - 2.f * r.x * r.x - 2.f * r.y * r.y;
	matrix.m[2][3] = 0;

	matrix.m[3][0] = 0;
	matrix.m[3][1] = 0;
	matrix.m[3][2] = 0;
	matrix.m[3][3] = 1;

	return matrix;
}

template<typename T>
Matrix<T, 4, 4> MatrixTRSOperations<T>::GetScaleMatrix(const Vector3D<T>& scale)
{
	Matrix<T, 4, 4> sm;

	sm.m[0][0] = scale.x; sm.m[0][1] = 0;		sm.m[0][2] = 0;		  sm.m[0][3] = 0;
	sm.m[1][0] = 0;		  sm.m[1][1] = scale.y; sm.m[1][2] = 0;		  sm.m[1][3] = 0;
	sm.m[2][0] = 0;		  sm.m[2][1] = 0;		sm.m[2][2] = scale.z; sm.m[2][3] = 0;
	sm.m[3][0] = 0;		  sm.m[3][1] = 0;		sm.m[3][2] = 0;		  sm.m[3][3] = 1;

	return sm;
}