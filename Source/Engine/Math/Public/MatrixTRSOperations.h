#pragma once

#include "Matrix.h"
#include "Vector3.h"
#include "Quaternion.h"

template<typename T>
class MatrixTRSOperations
{
public:

	static Matrix<T, 4, 4> GetPositionMatrix(const Vector3D<T>& position);

	static Matrix<T, 4, 4> GetRotationMatrix(const Quaternion<T>& r /*rotation*/);

	static Matrix<T, 4, 4> GetScaleMatrix(const Vector3D<T>& scale);
};