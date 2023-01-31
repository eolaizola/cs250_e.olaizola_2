/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

Project: cs250_e.olaizola_1
Filename: Matrix4.cpp

Author: Eritz 0laizola
Login: e.olaizola
StudentID:  540001219
Creation date: 01/09/2023
----------------------------------------------------------------------------------------------------------*/

#include "Matrix4.h"
#include "MathUtilities.h"
#include <stdexcept>

namespace Utils //Extra utils that can help
{

	/*
    *
    * \brief Computes 3x3 matrix determinant
    *
    */
	float Determinant3x3(float mm00, float mm01, float mm02, float mm10, float mm11, float mm12, float mm20, float mm21, float mm22)
	{
		//Compute the diagonals
		float diag1 = mm00 * mm11 * mm22;
		float diag2 = mm01 * mm12 * mm20;
		float diag3 = mm02 * mm10 * mm21;

		float diag4 = mm02 * mm11 * mm20;
		float diag5 = mm01 * mm10 * mm22;
		float diag6 = mm00 * mm12 * mm21;

		//Compute the value of the determimant
		float total = diag1 + diag2 + diag3 - diag4 - diag5 - diag6;
		return total;
	}

	int Round(float x)
	{
		int integer = x;
		float fl = x - integer;

		if (fl < 0.5f)
			x = integer;
		else
			x = ++integer;

		return x;
	}
}


/*
*
* \brief Default Constructor
*
*/
Matrix4::Matrix4(void)
{
	Zero();
}

/*
*
* \brief Copy Constructor
*
*/
Matrix4::Matrix4(const Matrix4& rhs)
{
	for (int i = 0; i < Utils::totalSize; i++)
		v[i] = rhs.v[i];
}

/*
*
* \brief Custom Constructor
* 
*/
Matrix4::Matrix4(float mm00, float mm01, float mm02, float mm03, float mm10, float mm11, float mm12, float mm13, float mm20, float mm21, float mm22, float mm23, float mm30, float mm31, float mm32, float mm33)
{
	v[0] = mm00;
	v[1] = mm01;
	v[2] = mm02;
	v[3] = mm03;
	v[4] = mm10;
	v[5] = mm11;
	v[6] = mm12;
	v[7] = mm13;
	v[8] = mm20;
	v[9] = mm21;
	v[10] = mm22;
	v[11] = mm23;
	v[12] = mm30;
	v[13] = mm31;
	v[14] = mm32;
	v[15] = mm33;
}

/*
*
* \brief Assign a matrix to another
*
* \return Matrix4&: The new Matrix
*
*/
Matrix4& Matrix4::operator=(const Matrix4& rhs)
{
	for (int i = 0; i < Utils::totalSize; i++)
		v[i] = rhs.v[i];

	return *this;
}

/*
*
* \brief Multiply a Vector with the matrix
*
* \return Vector4: The new point
*
*/
Vector4 Matrix4::operator*(const Vector4& rhs) const
{
	Vector4 result;
	for(int i = 0; i < Utils::size; i++)
	{
		Vector4 temp;//Temp vecor to store the rows

		for (int j = 0; j < Utils::size; j++)
		{
			temp.v[j] = m[i][j];//Store the values
		}

		result.v[i] = temp.Dot(rhs); //Perform dot product to store the result
	}

	return result;
}

/*
*
* \brief Multiply a Point with the matrix
*
* \return Point4: The new point
*
*/
Point4 Matrix4::operator*(const Point4& rhs) const
{
	Point4 result;
	for(int i = 0; i < Utils::size; i++)
	{
		Point4 temp;//Temp vecor to store the rows

		for (int j = 0; j < Utils::size; j++)
		{
			temp.v[j] = m[i][j];//Store the values
		}

		result.v[i] = temp.x * rhs.x + temp.y * rhs.y + temp.z * rhs.z + temp.w * rhs.w;; //Perform dot product to store the result
	}

	return result;
}

/*
*
* \brief Add between two matrices
*
* \return Matrix4: The new matrix
*
*/
Matrix4 Matrix4::operator+(const Matrix4& rhs) const
{
	Matrix4 result;

	for (int i = 0; i < Utils::totalSize; i++)
		result.v[i] = v[i] + rhs.v[i];

	return result;
}


/*
*
* \brief Substract between two matrices
*
* \return Matrix4: The new matrix
*
*/
Matrix4 Matrix4::operator-(const Matrix4& rhs) const
{
	Matrix4 result;

	for (int i = 0; i < Utils::totalSize; i++)
		result.v[i] = v[i] - rhs.v[i];

	return result;
}

/*
*
* \brief Multiply two matrices
*
* \return Matrix4: The new matrix
*
*/
Matrix4 Matrix4::operator*(const Matrix4& rhs) const
{
	Matrix4 result;
	Vector4 vec1;//Vectors to store data
	Vector4 vec2;//Vectors to store data


	for(int i = 0; i < Utils::size; i++)
	{
		for (int j = 0; j < Utils::size; j++)
		{
			for (int k = 0; k < Utils::size; k++)
			{
				//Get the row/column
				vec1.v[k] = m[i][k];
				vec2.v[k] = rhs.m[k][j];
			}

			//Perform dot product to get the value
			result.m[i][j] = vec1.Dot(vec2);
		}
	}
	return result;
}

/*
*
* \brief Add between two matrices
*
* \return Matrix4&: The new matrix (this)
*
*/
Matrix4& Matrix4::operator+=(const Matrix4& rhs)
{

	for (int i = 0; i < Utils::totalSize; i++)
		v[i] = v[i] + rhs.v[i];

	return *this;
}

/*
*
* \brief Substract between two matrices
*
* \return Matrix4&: The new matrix (this)
*
*/
Matrix4& Matrix4::operator-=(const Matrix4& rhs)
{

	for (int i = 0; i < Utils::totalSize; i++)
		v[i] = v[i] - rhs.v[i];

	return *this;
}

/*
*
* \brief Multiply two matrices
*
* \return Matrix4&: The new matrix (this)
*
*/
Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
	Matrix4 result;
	Vector4 vec1;//Vectors to store data
	Vector4 vec2;//Vectors to store data

	for (int i = 0; i < Utils::size; i++)
	{
		for (int j = 0; j < Utils::size; j++)
		{
			for (int k = 0; k < Utils::size; k++)
			{
				//Get the row/column
				vec1.v[k] = m[i][k];
				vec2.v[k] = rhs.m[k][j];
			}

			//Perform dot product to get the value
			result.m[i][j] = vec1.Dot(vec2);
		}
	}

	*this = result;
	return *this;
}

/*
*
* \brief Multiply the elements by rhs, the given value
*
* \return Matrix4: The new matrix
*
*/
Matrix4 Matrix4::operator*(const float rhs) const
{
	Matrix4 result;

	for (int i = 0; i < Utils::totalSize; i++)
		result.v[i] = v[i] * rhs;

	return result;
}

/*
*
* \brief Divide the elements by rhs, the given value
*
* \return Matrix4: The new matrix
*
*/
Matrix4 Matrix4::operator/(const float rhs) const
{
	//Sanity check
	if (isZero(rhs))
		throw std::runtime_error("Division by zero");

	Matrix4 result;

	for (int i = 0; i < Utils::totalSize; i++)
		result.v[i] = v[i] / rhs;

	return result;
}

/*
*
* \brief Multiply the elements by rhs, the given value
*
* \return Matrix4&: The new matrix (this)
*
*/
Matrix4& Matrix4::operator*=(const float rhs)
{
	for (int i = 0; i < Utils::totalSize; i++)
		v[i] *= rhs;

	return *this;
}

/*
*
* \brief Divide the elements by rhs, the given value
*
* \return Matrix4&: The new matrix (this)
*
*/
Matrix4& Matrix4::operator/=(const float rhs)
{
	//Sanity check
	if(isZero(rhs))
		throw std::runtime_error("Division by zero");

	for (int i = 0; i < Utils::totalSize; i++)
		v[i] /= rhs;

	return *this;
}

/*
*
* \brief Checks if the matrices are equal
*
* \return bool: False if they are not equal
*
*/
bool Matrix4::operator==(const Matrix4& rhs) const
{
	for (int i = 0; i < Utils::totalSize; i++)
		if (!isEqual(v[i], rhs.v[i]))
			return false;

	return true;
}

/*
*
* \brief Checks if the matrices are not equal
*
* \return bool: True if they are not equal
*
*/
bool Matrix4::operator!=(const Matrix4& rhs) const
{
	for (int i = 0; i < Utils::totalSize; i++)
		if (!isEqual(v[i], rhs.v[i])) //If the two elements are not equal, then the matrices are different
			return true;

	return false;
}

/*
*
* \brief Perform the determinant of matrix
*
* \return float: The value of the determinant
*
*/
float Matrix4::Determinant() const
{
	//Perform the determinant
	float m1 = v[0] * Utils::Determinant3x3(v[5], v[6], v[7], v[9], v[10], v[11], v[13], v[14], v[15]);
	float m2 = v[4] * Utils::Determinant3x3(v[1], v[2], v[3], v[9], v[10], v[11], v[13], v[14], v[15]);
	float m3 = v[8] * Utils::Determinant3x3(v[1], v[2], v[3], v[5], v[6], v[7], v[13], v[14], v[15]);
	float m4 = v[12] * Utils::Determinant3x3(v[1], v[2], v[3], v[5], v[6], v[7], v[9], v[10], v[11]);

	float total = m1 - m2 + m3 - m4;

	return total;
}

/*
*
* \brief Perform the invers matrix
* 
* \return Matrix4: The invers of the matrix
*
*/
Matrix4 Matrix4::Inverse() const
{
	float determ = Determinant();

	//Sanity check
	if(isZero(determ))
	{
		throw std::runtime_error("Division by zero");
	}

	Matrix4 result;
	
	//Perform the transpose and adjugate
	//Then divide by the determinant of the 4x4 matrix

	//First Row
	result.v[0] = Utils::Determinant3x3(v[5], v[6], v[7], v[9], v[10], v[11], v[13], v[14], v[15]) / determ;
	result.v[4] = -Utils::Determinant3x3(v[4], v[6], v[7], v[8], v[10], v[11], v[12], v[14], v[15]) / determ;
	result.v[8] = Utils::Determinant3x3(v[4], v[5], v[7], v[8], v[9], v[11], v[12], v[13], v[15]) / determ;
	result.v[12] = -Utils::Determinant3x3(v[4], v[5], v[6], v[8], v[9], v[10], v[12], v[13], v[14]) / determ;

	//Second row
	result.v[1] = -Utils::Determinant3x3(v[1], v[2], v[3], v[9], v[10], v[11], v[13], v[14], v[15]) / determ;
	result.v[5] = Utils::Determinant3x3(v[0], v[2], v[3], v[8], v[10], v[11], v[12], v[14], v[15]) / determ;
	result.v[9] = -Utils::Determinant3x3(v[0], v[1], v[3], v[8], v[9], v[11], v[12], v[13], v[15]) / determ;
	result.v[13] = Utils::Determinant3x3(v[0], v[1], v[2], v[8], v[9], v[10], v[12], v[13], v[14]) / determ;

	//Third row
	result.v[2] = Utils::Determinant3x3(v[1], v[2], v[3], v[5], v[6], v[7], v[13], v[14], v[15]) / determ;
	result.v[6] = -Utils::Determinant3x3(v[0], v[2], v[3], v[4], v[6], v[7], v[12], v[14], v[15]) / determ;
	result.v[10] = Utils::Determinant3x3(v[0], v[1], v[3], v[4], v[5], v[7], v[12], v[13], v[15]) / determ;
	result.v[14] = -Utils::Determinant3x3(v[0], v[1], v[2], v[4], v[5], v[6], v[12], v[13], v[14]) / determ;

	//Fourth row
	result.v[3] = -Utils::Determinant3x3(v[1], v[2], v[3], v[5], v[6], v[7], v[9], v[10], v[11]) / determ;
	result.v[7] = Utils::Determinant3x3(v[0], v[2], v[3], v[4], v[6], v[7], v[8], v[10], v[11]) / determ;
	result.v[11] = -Utils::Determinant3x3(v[0], v[1], v[3], v[4], v[5], v[7], v[8], v[9], v[11]) / determ;
	result.v[15] = Utils::Determinant3x3(v[0], v[1], v[2], v[4], v[5], v[6], v[8], v[9], v[10]) / determ;

	return result;
}

/*
*
* \brief Set this to zero matrix
*
*/
void Matrix4::Zero(void)
{
	for (int i = 0; i < Utils::totalSize; i++)
		v[i] = 0;
}

/*
* 
* \brief Set this to the identity matrix
* 
*/
void Matrix4::Identity(void)
{
	for (int i = 0; i < Utils::size; i++)
	{
		for (int j = 0; j < Utils::size; j++)
		{
			//Set to 1 or 0, to do the identity
			if (i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
		}
	}
}

void Matrix4::RotationMatrix(float x, float y, float z)
{
	Matrix4 Rot_x;
	Matrix4 Rot_y;
	Matrix4 Rot_z;

	Rot_x.Identity();
	Rot_y.Identity();
	Rot_z.Identity();

	x = (x * Utils::pi) / 180;
	y = (y * Utils::pi) / 180;
	z = (z * Utils::pi) / 180;


	Rot_x.m[1][1] = cos(x);
	Rot_x.m[1][2] = -sin(x);
	Rot_x.m[2][1] = sin(x);
	Rot_x.m[2][2] = cos(x);

	Rot_y.m[0][0] = cos(y);
	Rot_y.m[2][0] = -sin(y);
	Rot_y.m[2][2] = cos(y);
	Rot_y.m[0][2] = sin(y);

	Rot_z.m[0][0] = cos(z);
	Rot_z.m[1][0] = sin(z);
	Rot_z.m[0][1] = -sin(z);
	Rot_z.m[1][1] = cos(z);

	*this = Rot_x * Rot_y * Rot_z;
}

void Matrix4::TranslationMatrix(float x, float y, float z)
{
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
}

void Matrix4::ScaleMatrix(float x, float y, float z)
{
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
}
