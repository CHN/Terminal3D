#pragma once

#include <cstdint>
#include <cstddef>
#include <cmath>

template<typename T>
struct Quaternion
{
    T x, y, z, w;

    Quaternion() : x(0), y(0), z(0), w(1) {}
    Quaternion(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

    void MultiplyInPlace(const Quaternion& rhs)
    {
		T t_x = y * rhs.z - z * rhs.y + x * rhs.w + w * rhs.x;
		T t_y = z * rhs.x - x * rhs.z + y * rhs.w + w * rhs.y;
		T t_z = x * rhs.y - y * rhs.x + z * rhs.w + w * rhs.z;
		T t_w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;

        x = t_x;
        y = t_y;
        z = t_z;
        w = t_w;
    }

    Quaternion operator*(const Quaternion& rhs) const
    {
        Quaternion q;

        q.MultiplyInPlace(rhs);

        return q;
    }

	Quaternion operator*=(const Quaternion& rhs) const
	{
		return *this * rhs;
	}

    void Conjugate()
    {
        x = -x;
        y = -y;
        z = -z;
    }
    // TODO: Add math template types
    double Norm() const
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    void Normalize()
    {
		T norm = 1.0 / Norm();
		x *= norm;
		y *= norm;
		z *= norm;
		w *= norm;
    }

    void Inverse()
    {
		T norm = 1.0 / Norm();
		Conjugate();
		x *= norm;
		y *= norm;
		z *= norm;
		w *= norm;
    }

    void SetRotation(const Vector3D<T>& rotationAxis, T angleInRadians)
    {
        x = rotationAxis.x * std::sin(angleInRadians * 0.5);
        y = rotationAxis.y * std::sin(angleInRadians * 0.5);
        z = rotationAxis.z * std::sin(angleInRadians * 0.5);
        w = std::cos(angleInRadians * 0.5);
    }

	void RotateByAngleAxisInPlace(const Vector3D<T>& rotationAxis, T angleInRadians)
	{
		Quaternion q;
		q.SetRotation(rotationAxis, angleInRadians);

		MultiplyInPlace(q);
		Normalize();
	}

    Quaternion RotateByAngleAxis(const Vector3D<T>& rotationAxis, T angleInRadians) const
    {
        Quaternion q;
        q.SetRotation(rotationAxis, angleInRadians);
 
        q.MultiplyInPlace(*this);
        q.Normalize();

		return q;
    }
};

using QuaternionF = Quaternion<float>;
using QuaternionD = Quaternion<double>;