#pragma once

#include <cstdint>
#include <cstddef>
#include <sstream>
#include <iomanip>
#include <cmath>

template<typename T>
struct Vector2D
{
    T x, y;

    Vector2D() = default;
    Vector2D(T x, T y) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& rhs) const
    {
        return Vector2D(x + rhs.x, y + rhs.y);
    }

    Vector2D operator-(const Vector2D& rhs) const
    {
        return Vector2D(x - rhs.x, y - rhs.y);
    }

    Vector2D operator*(const Vector2D& rhs) const
    {
        return Vector2D(x * rhs.x, y * rhs.y);
    }

    Vector2D operator*(T value) const
    {
        return Vector2D(x * value, y * value);
    }

    T Dot(const Vector2D& rhs) const
    {
        return x * rhs.x + y * rhs.y;
    }

    T SqrMagnitude() const
    {
        return x * x + y * y;
    }

    T Magnitude() const
    {
        return sqrt(SqrMagnitude());
    }

    template<typename TOther>
    explicit operator TOther() const
    {
        return TOther(x, y);
    }

    Vector2D Normalize() const
    {
        return *this * (1 / Magnitude());
    }

    std::string toString(uint32_t length = 6, uint32_t precision = 3) const
    {
        std::stringstream content;

        content << x << ',' << y;

        return content.str();
    }

    static const Vector2D<T> Zero;
    static const Vector2D<T> One;
};

template<typename T>
const Vector2D<T> Vector2D<T>::Zero = Vector2D<T>(0, 0);

template<typename T>
const Vector2D<T> Vector2D<T>::One = Vector2D<T>(1, 1);

template<typename T>
Vector2D<T> operator*(T value, Vector2D<T> vector)
{
    return Vector2D(vector.x * value, vector.y * value);
}

using Vector2DF = Vector2D<float>;
using Vector2DI = Vector2D<int>;
using Vector2DLI = Vector2D<long int>;
using Vector2DD = Vector2D<double>;