#ifndef MATRIX4_H
#define MATRIX4_H

#include "Point4.h"
#include "Vector4.h"
#include <stdio.h> // printf


namespace Utils
{
    //Size for the loops
    const int size = 4;
    const int totalSize = 16;
    const float pi = 3.141592653589f;

    float Determinant3x3(float mm00, float mm01, float mm02, float mm10, float mm11, float mm12, float mm20, float mm21, float mm22);
    int Round(float x);
}

class Matrix4
{
  public:
    union
    {
        float m[4][4];
        float v[16];
    };
    /*
            This union lets us access the data in multiple ways
            All of these are modifying the same location in memory
            Matrix4 mtx;
            mtx.m[2][2] = 1.0f;
            mtx.v[10] = 2.0f;
        */

    // Default constructor should initialize to zeroes
    Matrix4(void);

    // Copy constructor, copies every entry from the other matrix.
    Matrix4(const Matrix4 & rhs);

    // Non-default constructor, self-explanatory
    Matrix4(float mm00, float mm01, float mm02, float mm03,
            float mm10, float mm11, float mm12, float mm13,
            float mm20, float mm21, float mm22, float mm23,
            float mm30, float mm31, float mm32, float mm33);

    // Assignment operator, does not need to handle self-assignment
    Matrix4 & operator=(const Matrix4 & rhs);

    // Multiplying a Matrix4 with a Vector4 or a Point4
    Vector4 operator*(const Vector4 & rhs) const;
    Point4  operator*(const Point4 & rhs) const;

    // Basic Matrix arithmetic operations
    Matrix4 operator+(const Matrix4 & rhs) const;
    Matrix4 operator-(const Matrix4 & rhs) const;
    Matrix4 operator*(const Matrix4 & rhs) const;

    // Similar to the three above except they modify the original
    Matrix4 & operator+=(const Matrix4 & rhs);
    Matrix4 & operator-=(const Matrix4 & rhs);
    Matrix4 & operator*=(const Matrix4 & rhs);

    // Scale/Divide the entire matrix by a float
    Matrix4 operator*(const float rhs) const;
    Matrix4 operator/(const float rhs) const;
    // Same as previous
    Matrix4 & operator*=(const float rhs);
    Matrix4 & operator/=(const float rhs);

    // Comparison operators which should use an epsilon defined in
    // MathUtilities.h to see if the value is within a certain range
    // in which case we say they are equivalent.
    bool operator==(const Matrix4 & rhs) const;
    bool operator!=(const Matrix4 & rhs) const;

    // Computes and returns the determinant of the matrix
    float Determinant() const;

    // Computes and returns the inverse of the matrix
    Matrix4 Inverse() const;

    // Zeroes out the entire matrix
    void Zero(void);

    // Builds the identity matrix
    void Identity(void);

    void RotationMatrix(float x, float y, float z);
    void TranslationMatrix(float x, float y, float z);
    void ScaleMatrix(float x, float y, float z);

    // Already implemented, simple print function
    void Print(void) const
    {
        printf("--------------------------\n");
        printf("%5.3f %5.3f %5.3f %5.3f\n", m[0][0], m[0][1], m[0][2], m[0][3]);
        printf("%5.3f %5.3f %5.3f %5.3f\n", m[1][0], m[1][1], m[1][2], m[1][3]);
        printf("%5.3f %5.3f %5.3f %5.3f\n", m[2][0], m[2][1], m[2][2], m[2][3]);
        printf("%5.3f %5.3f %5.3f %5.3f\n", m[3][0], m[3][1], m[3][2], m[3][3]);
        printf("--------------------------\n");
    }
};

#endif