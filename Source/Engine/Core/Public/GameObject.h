#pragma once

#include "Math.hpp"
#include "MatrixTRS.h"

// Consider migrating to ECS

class GameObject
{
public:

	Vector3DF GetPosition() const { return transformationMatrix.GetPosition(); }
	virtual void SetPosition(const Vector3DF& val) 
	{ 
		transformationMatrix.SetPosition(val);
	}

	Vector3DF GetScale() const { return transformationMatrix.GetScale(); }
	virtual void SetScale(const Vector3DF& val)
	{
		transformationMatrix.SetScale(val);
	}

	QuaternionF GetRotation() const { return transformationMatrix.GetRotation(); }
	virtual void SetRotation(const QuaternionF& val)
	{ 
		transformationMatrix.SetRotation(val);
	}

	const MatrixF4x4& GetTransformationMatrix() const { return transformationMatrix; }

	virtual ~GameObject() = default;

protected:

	MatrixTRS<float, true /*Dirting should be considered*/> transformationMatrix;
};