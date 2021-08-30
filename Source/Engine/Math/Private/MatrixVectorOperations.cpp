#include "MatrixVectorOperations.h"

template<typename T>
Vector3D<T> MatrixVectorOperations<T>::MultiplyByVector3D(const Matrix<T, 4, 4>& matrix, const Vector3D<T>& vector)
{
	Vector3D<T> outVector;

	for (size_t i = 0; i < 3; ++i)
	{
		outVector.x += matrix.m[i][0] * vector.x;
		outVector.y += matrix.m[i][1] * vector.y;
		outVector.z += matrix.m[i][2] * vector.z;
	}

	return outVector;
}

template<typename T>
Vector3D<T> MatrixVectorOperations<T>::MultiplyByVector3DHomogenously(const Matrix<T, 4, 4>& matrix, const Vector3D<T>& vector)
{
	Vector3D<T> outVector;
	T w = 0;

	for (size_t i = 0; i < 4; ++i)
	{
		outVector.x += matrix.m[i][0] * vector.x;
		outVector.y += matrix.m[i][1] * vector.y;
		outVector.z += matrix.m[i][2] * vector.z;
		w += matrix.m[i][3];
	}

	w = T(1) / w;

	outVector.x *= w;
	outVector.y *= w;
	outVector.z *= w;

	return outVector;
}
