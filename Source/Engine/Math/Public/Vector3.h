#pragma once

#include <cstdint>
#include <cstddef>
#include <sstream>
#include <iomanip>
#include <cmath>

template<typename T>
struct Vector3D
{
    T x, y, z;

    Vector3D() = default;
    Vector3D(T x, T y, T z) : x(x), y(y), z(z) {}

    Vector3D operator+(const Vector3D& rhs) const
    {
        return Vector3D(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Vector3D operator-(const Vector3D& rhs) const
    {
        return Vector3D(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    Vector3D operator*(const Vector3D& rhs) const
    {
        return Vector3D(x * rhs.x, y * rhs.y, z * rhs.z);
    }

    Vector3D operator*(T value) const
    {
        return Vector3D(x * value, y * value, z * value);
    }

    Vector3D Cross(const Vector3D& rhs) const
    {
        Vector3D vector;
        Cross(*this, rhs, &vector);
        return vector;
    }

    static Vector3D Cross(const Vector3D& lhs, const Vector3D& rhs, Vector3D* const outV)
    {
        *outV = Vector3D(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
    }

    T Dot(const Vector3D& rhs) const
    {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    T SqrMagnitude() const
    {
        return x * x + y * y + z * z;
    }

    T Magnitude() const
    {
        return sqrt(SqrMagnitude());
    }

    Vector3D Normalize() const
    {
        return *this * (1 / Magnitude());
    }

    template<typename TOther>
    explicit operator TOther() const
    {
        return TOther(x, y, z);
    }

    std::string toString(uint32_t length = 6, uint32_t precision = 3) const
    {
        std::stringstream content;

        content << x << ',' << y << ',' << z;

        return content.str();
    }

    static const Vector3D<T> Zero;
    static const Vector3D<T> One;
};

template<typename T>
const Vector3D<T> Vector3D<T>::Zero(0, 0, 0);

template<typename T>
const Vector3D<T> Vector3D<T>::One(1, 1, 1);

template<typename T>
Vector3D<T> operator*(T value, Vector3D<T> vector)
{
    return Vector3D(vector.x * value, vector.y * value, vector.z * value);
}

using Vector3DF = Vector3D<float>;
using Vector3DI = Vector3D<int>;
using Vector3DLI = Vector3D<long int>;
using Vector3DD = Vector3D<double>;