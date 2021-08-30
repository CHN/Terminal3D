#pragma once

#include "Matrix.h"
#include "Vector3.h"

template<typename T>
class MatrixVectorOperations
{
public:
	
	static Vector3D<T> MultiplyByVector3D(const Matrix<T, 4, 4>& matrix, const Vector3D<T>& vector);

	static Vector3D<T> MultiplyByVector3DHomogenously(const Matrix<T, 4, 4>& matrix, const Vector3D<T>& vector);
};