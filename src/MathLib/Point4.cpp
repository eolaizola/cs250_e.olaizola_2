/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

Project: cs250_e.olaizola_1
Filename: Point4.cpp

Author: Eritz 0laizola
Login: e.olaizola
StudentID:  540001219
Creation date: 01/09/2023
----------------------------------------------------------------------------------------------------------*/

#include "Point4.h"
#include "MathUtilities.h"
#include <stdexcept>

/*
*
* \brief Default Constructor
*
*/
Point4::Point4(void)
{
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

/*
*
* \brief Copy Constructor
*
*/
Point4::Point4(const Point4& rhs)
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
Point4::Point4(float xx, float yy, float zz, float ww) : x(xx), y(yy), z(zz), w(ww)
{
}

/*
*
* \brief Assignment operator
* 
* \return Point4: The new point (this)
*
*/
Point4& Point4::operator=(const Point4& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;

	return *this;
}

/*
*
* \brief Negates the point
*
* \return Point4: The new point negated
*
*/
Point4 Point4::operator-(void) const
{
	return Point4(-x, -y, -z, -w);
}

/*
*
* \brief Substraction of 2 points
*
* \return Vector4: A vector, the result of the substraction
*
*/
Vector4 Point4::operator-(const Point4& rhs) const
{
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

/*
*
* \brief Addition of 2 points
*
* \return Point4: A Point, the result of the addition
*
*/
Point4 Point4::operator+(const Vector4& rhs) const
{
	return Point4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

/*
*
* \brief Addition of a point and a vector
*
* \return Point4: A Point, the result of the substraction
*
*/
Point4 Point4::operator-(const Vector4& rhs) const
{
	return Point4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

/*
*
* \brief Division of a point and a scalar
*
* \return Point4: A Point, the result of the division
*
*/
Point4 Point4::operator/(const float& rhs) const
{
	//Sanity check
	if (isZero(rhs))
	{
		throw std::runtime_error("Division by zero");
	}

	return Point4(x/rhs, y/rhs, z/rhs, w/rhs);
}

/*
*
* \brief Addition of a point and a vector
*
* \return Point4: A Point, the result of the addition
*
*/
Point4& Point4::operator+=(const Vector4& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}

/*
*
* \brief Substraction of a point and a vector
*
* \return Point4: A Point, the result of the substraction
*
*/
Point4& Point4::operator-=(const Vector4& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}

/*
*
* \brief Division of a point and a scalar
*
* \return Point4: A Point, the result of the substraction
*
*/
Point4& Point4::operator/=(const float& rhs)
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
* \brief Compare if the points are equal
*
* \return bool: True if they are equal
*
*/
bool Point4::operator==(const Point4& rhs) const
{
	for (int i = 0; i < 4; i++)
		if (!isEqual(x, rhs.x))
			return false;

	return true;
}

/*
*
* \brief Compare if the points are not equal
*
* \return bool: True if they are  not equal
*
*/
bool Point4::operator!=(const Point4& rhs) const
{
	for (int i = 0; i < 4; i++)
		if (!isEqual(x, rhs.x))
			return true;

	return false;
}

/*
*
* \brief Set the point to zeros
*
*/
void Point4::Zero(void)
{
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}
