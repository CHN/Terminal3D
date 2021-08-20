#pragma once

#include "Math.h"

// Consider migrating to ECS

class GameObject
{
public:

	GameObject() : m_Position(Vector3DF::Zero), m_Scale(Vector3DF::One) {}

	Vector3DF GetPosition() const { return m_Position; }
	virtual void SetPosition(Vector3DF val) 
	{ 
		m_Position = val;
		UpdateTransformationMatrixCache();
	}

	Vector3DF GetScale() const { return m_Scale; }
	virtual void SetScale(Vector3DF val) 
	{
		m_Scale = val;
		UpdateTransformationMatrixCache();
	}

	QuaternionF GetRotation() const { return m_Rotation; }
	virtual void SetRotation(QuaternionF val) 
	{ 
		m_Rotation = val;
		UpdateTransformationMatrixCache(); 
	}

	const MatrixF4x4& GetTransformationMatrix() const { return m_TransformationMatrixCache; }

	virtual ~GameObject() = default;

protected:

	Vector3DF m_Position;
	Vector3DF m_Scale;
	QuaternionF m_Rotation;

private:
	MatrixF4x4 m_TransformationMatrixCache;

	void UpdateTransformationMatrixCache(); // Consider using dirtying method
};