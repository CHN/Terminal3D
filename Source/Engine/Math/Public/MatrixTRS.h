#pragma once

#include "Matrix.h"
#include "Vector3.h"
#include "Quaternion.h"

#include "MatrixTRSOperations.h"

template<typename T, bool AutoUpdateMatrix = true>
class MatrixTRS : public Matrix<T, 4, 4>
{
public:

	MatrixTRS& operator=(const MatrixTRS& rhs) = default;

	MatrixTRS& operator=(const Matrix<T, 4, 4>& rhs)
	{
		this->Matrix<T, 4, 4>::operator=(rhs);

		return *this;
	}

	inline const Vector3D<T>& GetPosition() const { return m_Position; }
	inline void SetPosition(const Vector3D<T>& val)
	{
		m_Position = val; 

		if constexpr (AutoUpdateMatrix)
		{
			UpdateMatrix();
		}
	}

	inline const Vector3D<T>& GetScale() const { return m_Scale; }
	inline void SetScale(const Vector3D<T>& val)
	{ 
		m_Scale = val;

		if constexpr (AutoUpdateMatrix)
		{
			UpdateMatrix();
		}
	}

	inline const Quaternion<T>& GetRotation() const { return m_Rotation; }
	inline void SetRotation(const Quaternion<T>& val)
	{ 
		m_Rotation = val;

		if constexpr (AutoUpdateMatrix)
		{
			UpdateMatrix();
		}
	}

	void UpdateMatrix()
	{
		*this = MatrixTRSOperations<T>::GetPositionMatrix(m_Position) *
				MatrixTRSOperations<T>::GetRotationMatrix(m_Rotation) *
				MatrixTRSOperations<T>::GetScaleMatrix(m_Scale);
	}

	private:

	Vector3D<T> m_Position;
	Vector3D<T> m_Scale = Vector3D<T>::One;
	Quaternion<T> m_Rotation;
};