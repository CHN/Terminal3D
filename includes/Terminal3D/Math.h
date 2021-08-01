#pragma once

#include "TypeTraits.h"

#include <cstdint>
#include <stddef.h>
#include <type_traits>
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
const Vector3D<T> Vector3D<T>::Zero = Vector3D<T>(0, 0, 0);

template<typename T>
const Vector3D<T> Vector3D<T>::One = Vector3D<T>(1, 1, 1);

template<typename T>
Vector3D<T> operator*(T value, Vector3D<T> vector)
{
    return Vector3D(vector.x * value, vector.y * value, vector.z * value);
}

using Vector3DF = Vector3D<float>;
using Vector3DI = Vector3D<int>;
using Vector3DLI = Vector3D<long int>;
using Vector3DD = Vector3D<double>;


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

template<typename T, uint32_t RowCount, uint32_t ColumnCount>
struct Matrix
{
    T m[RowCount][ColumnCount];

    void Set(uint32_t row, uint32_t column, T value)
    {
        m[row][column] = value;
    }

    void SetRows(uint32_t row, T values[RowCount])
    {
        for (size_t i = 0; i < ColumnCount; ++i)
        {
            m[row][i] = values[i];
        }
    }

    void SetColumns(uint32_t column, T values[ColumnCount])
    {
        for (size_t i = 0; i < RowCount; ++i)
        {
            m[i][column] = values[i];
        }
    }

    Matrix operator+(const Matrix& rhs) const
    {
        Matrix matrix;

        for (size_t i = 0; i < RowCount * ColumnCount; ++i)
        {
            matrix.m[i] = matrix[i] + rhs.m[i];
        }     

        return matrix;
    }

    Matrix operator-(const Matrix& rhs) const
    {
        Matrix matrix;

        for (size_t i = 0; i < RowCount * ColumnCount; ++i)
        {
            matrix.m[i] = matrix[i] - rhs.m[i];
        }     

        return matrix;
    }

    template<uint32_t RowCountRHS, uint32_t ColumnCountRHS, std::enable_if_t<is_same_integral_v<RowCountRHS, ColumnCount>, bool> = true>
    Matrix<T, RowCount, ColumnCountRHS> operator*(const Matrix<T, RowCountRHS, ColumnCountRHS>& rhs) const
    {
        Matrix<T, RowCount, ColumnCountRHS> matrix;

        for (size_t i = 0; i < RowCount; ++i) // lhs
        {
            for (size_t j = 0; j < ColumnCountRHS; ++j) // result
            {
                matrix.m[i][j] = 0;

                for (size_t k = 0; k < ColumnCountRHS; ++k) // rhs
                {
                    matrix.m[i][j] += m[i][k] * rhs.m[k][j];
                }
            }
        }

        return matrix;
    }

    Matrix<T, RowCount, ColumnCount> operator*(T value) const
    {
        Matrix<T, RowCount, ColumnCount> matrix;

        for (size_t i = 0; i < RowCount; ++i)
        {
            for (size_t j = 0; j < ColumnCount; ++j)
            {
                matrix.m[i][j] = m[i][j] * value;
            }
        }

        return matrix;
    }

    Vector3D<T> operator*(const Vector3D<T>& vector) const
    {
        Vector3D<T> outVector;
        T temp[4] = { 0 };

        for (size_t i = 0; i < RowCount; ++i)
        {
            temp[i] += m[i][0] * vector.x;
            temp[i] += m[i][1] * vector.y;
            temp[i] += m[i][2] * vector.z;
            temp[i] += m[i][3];
        }

        outVector.x = temp[0] / temp[3];
        outVector.y = temp[1] / temp[3];
        outVector.z = temp[2];// / temp[3];

        return outVector;
    }

    Matrix ElementMultiply(const Matrix& rhs) const
    {
        return MatrixElementMultiply(*this, rhs);
    }

private:

    T invf(int i, int j) const {

        int o = 2+(j-i);

        i += 4 + o;
        j += 4 - o;

        #define e(a,b) m[(i+a) % 4][(j+b) % 4]

        T inv =
        + e(+1,-1)*e(+0,+0)*e(-1,+1)
        + e(+1,+1)*e(+0,-1)*e(-1,+0)
        + e(-1,-1)*e(+1,+0)*e(+0,+1)
        - e(-1,-1)*e(+0,+0)*e(+1,+1)
        - e(-1,+1)*e(+0,-1)*e(+1,+0)
        - e(+1,-1)*e(-1,+0)*e(+0,+1);

        return (o % 2) ? inv : -inv;

        #undef e
    }

public:

    template<typename Type = bool, std::enable_if_t<is_same_integral_v<RowCount, ColumnCount>, Type> = true>
    Matrix Inverse() const
    {
        Matrix matrix;

        for(int i = 0;i < RowCount; ++i)
        {
            for(int j = 0; j < ColumnCount; ++j)
            {
                matrix.m[i][j] = invf(i, j);
            }
        }

        double D = 0;

        for(int k = 0; k < RowCount; ++k) D += m[k][0] * matrix.m[0][k];

        if (D == 0) return matrix; // TODO: Handle with runtime assert

        D = 1.0 / D;

        for (int i = 0; i < RowCount; ++i)
        {
            for (int j = 0; j < ColumnCount; ++j)
            {
                matrix.m[i][j] *= D;
            }
        }
        
        return matrix;
    }

    std::string toString(uint32_t length = 6, uint32_t precision = 3) const
    {
        std::stringstream content;

        for (size_t i = 0; i < RowCount; ++i)
        {
            content << '|';

            for (size_t j = 0; j < ColumnCount; ++j)
            {
                content << std::setw(length) << std::setprecision(precision) << std::right <<  m[i][j] << ' ';
            }

            content << "|\n";
        }

        return content.str();
    }
}; 

template<typename T, uint32_t RowCount, uint32_t ColumnCount>
Matrix<T, RowCount, ColumnCount> MatrixElementMultiply(const Matrix<T, RowCount, ColumnCount>& lhs, const Matrix<T, RowCount, ColumnCount>& rhs)
{
    Matrix<T, RowCount, ColumnCount> matrix;

    for (size_t i = 0; i < RowCount; ++i)
    {
        for (size_t j = 0; j < ColumnCount; ++j)
        {
            matrix.m[i][j] = lhs.m[i][j] * rhs.m[i][j];
        }  
    }     

    return matrix;
}

using MatrixI3x3 = Matrix<int, 3, 3>;
using MatrixI3x4 = Matrix<int, 3, 4>;
using MatrixI4x3 = Matrix<int, 4, 3>;
using MatrixI4x4 = Matrix<int, 4, 4>;

using MatrixF3x3 = Matrix<float, 3, 3>;
using MatrixF3x4 = Matrix<float, 3, 4>;
using MatrixF4x3 = Matrix<float, 4, 3>;
using MatrixF4x4 = Matrix<float, 4, 4>;

using MatrixD3x3 = Matrix<double, 3, 3>;
using MatrixD3x4 = Matrix<double, 3, 4>;
using MatrixD4x3 = Matrix<double, 4, 3>;
using MatrixD4x4 = Matrix<double, 4, 4>;

using Matrix3x3 = MatrixF3x3;
using Matrix3x4 = MatrixF3x4;
using Matrix4x3 = MatrixF4x3;
using Matrix4x4 = MatrixF4x4;

constexpr double PI = 3.14159265358979323846;