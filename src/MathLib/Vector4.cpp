/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

Project: cs250_e.olaizola_1
Filename: Vecor4.cpp

Author: Eritz 0laizola
Login: e.olaizola
StudentID:  540001219
Creation date: 01/09/2023
----------------------------------------------------------------------------------------------------------*/

#include "Vector4.h"
#include "MathUtilities.h"
#include <stdexcept>

/*
*
* \brief Default Constructor
*
*/
Vector4::Vector4(void)
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}


/*
*
* \brief Copy Constructor
*
*/
Vector4::Vector4(const Vector4& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;
}

/*
*
* \brief Custom Constructor
*
*/
Vector4::Vector4(float xx, float yy, float zz, float ww) : x(xx), y(yy), z(zz), w(ww)
{
}

/*
*
* \brief Assignment operator
* 
* \return Vector4: The new vector (this)
*
*/
Vector4& Vector4::operator=(const Vector4& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;
	return *this;
}

/*
*
* \brief Negate the vector
*
* \return Vector4: The new vector
*
*/
Vector4 Vector4::operator-(void) const
{
	return Vector4(-x, -y, -z, -w);
}


/*
*
* \brief Addition of two vectors
*
* \return Vector4: The new vector
*
*/
Vector4 Vector4::operator+(const Vector4& rhs) const
{
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}


/*
*
* \brief Substraction of two vectors
*
* \return Vector4: The new vector
*
*/
Vector4 Vector4::operator-(const Vector4& rhs) const
{
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}


/*
*
* \brief Multoplication of a vector and a scalar
*
* \return Vector4: The new vector
*
*/
Vector4 Vector4::operator*(const float rhs) const
{
	return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
}


/*
*
* \brief Division of a vector and a scalar
*
* \return Vector4: The new vector
*
*/
Vector4 Vector4::operator/(const float rhs) const
{
	//Sanity check
	if (isZero(rhs))
	{
		throw std::runtime_error("Division by zero");
	}

	return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
}


/*
*
* \brief Addition of two vectors
*
* \return Vector4: The new vector (this)
*
*/
Vector4& Vector4::operator+=(const Vector4& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}

/*
*
* \brief Substraction of two vectors
*
* \return Vector4: The new vector (this)
*
*/
Vector4& Vector4::operator-=(const Vector4& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}

/*
*
* \brief Multiplication of a vector and a scalar
*
* \return Vector4: The new vector (this)
*
*/
Vector4& Vector4::operator*=(const float rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	w *= rhs;
	return *this;
}

/*
*
* \brief Division of a vector and a scalar
*
* \return Vector4: The new vector (this)
*
*/
Vector4& Vector4::operator/=(const float rhs)
{
	if (isZero(rhs))
	{
		throw std::runtime_error("Division by zero");
	}

	x /= rhs;
	y /= rhs;
	z /= rhs;
	w /= rhs;
	return *this;
}

/*
*
* \brief Checks if the two vectors are equal
*
* \return bool: True if they are equal
*
*/
bool Vector4::operator==(const Vector4& rhs) const
{
	for (int i = 0; i < 4; i++)
		if (!isEqual(x, rhs.x))
			return false;

	return true;
}

/*
*
* \brief Checks if the two vectors are not equal
*
* \return bool: True if they are not equal
*
*/
bool Vector4::operator!=(const Vector4& rhs) const
{
	for (int i = 0; i < 4; i++)
		if (!isEqual(x, rhs.x))
			return true;

	return false;
}

/*
*
* \brief Computes the dot product between 2 vectors
*
* \return float: The value of the dot product
*
*/
float Vector4::Dot(const Vector4& rhs) const
{
	float result = x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
	return result;
}

/*
*
* \brief Computes the cross product between 2 vectors
*
* \return Vector4: The Vector4 of the cross product
*
*/
Vector4 Vector4::Cross(const Vector4& rhs) const
{
	float mX = y * rhs.z - z * rhs.y;
	float mY = z * rhs.x - x * rhs.z;
	float mZ = x * rhs.y - y * rhs.x;

	return Vector4(mX, mY, mZ);
}

/*
*
* \brief Computes the length of the vector
*
* \return float: The length of the vector
*
*/
float Vector4::Length(void) const
{
	return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

/*
*
* \brief Computes the length of the vector to the square
*
* \return float: The length of the vector to the square
*
*/
float Vector4::LengthSq(void) const
{
	float lenth = (x * x) + (y * y) + (z * z) + (w * w);
	return lenth;
}

/*
*
* \brief Normalize the vector
*
*/
void Vector4::Normalize(void)
{
	float lenth = Length();

	if (isZero(lenth))
	{
		throw std::runtime_error("Division by zero");
	}

	x /= lenth;
	y /= lenth;
	z /= lenth;
	w /= lenth;
}

/*
*
* \brief Set the vector to all zeros
*
*/
void Vector4::Zero(void)
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}
