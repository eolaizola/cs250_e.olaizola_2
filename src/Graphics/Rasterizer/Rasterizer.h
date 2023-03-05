/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

Project: cs250_e.olaizola_2
Filename: Rasterizer.h

Author: Eritz 0laizola
Login: e.olaizola
StudentID:  540001219
Creation date: 01/30/2023
----------------------------------------------------------------------------------------------------------*/

#pragma once
#include "../src/MathLib/Point4.h"
#include "../src/MathLib/Matrix4.h"
#include "../src/Graphics/Camera/Camera.h"

//Color class for convenience
struct Color
{
	Color(){}
	Color(const char rr, const char gg, const char bb)
	{
		r = rr;
		g = gg;
		b = bb;
	}

	char r = 0;
	char g = 0;
	char b = 0;
};

namespace Rasterizer
{
	//Draw line
	void DrawLine(const Point4& p1, const Point4& p2, const Color col);
	void DrawVerticalLine(const Point4& p1, const Point4& p2, const Color col);
	void DrawHorizontalLine(const Point4& p1, const Point4& p2, const Color col);
	void DrawDiagonalLine(const Point4& p1, const Point4& p2, const Color col);

	//Draw Triangle
	bool DetermineCase(float y0, float y1, float y2, int& t, int& m, int& b);
	void DrawTriangle(const Point4& vertex1, const Point4& vertex2, const Point4& vertex3, const Color col);

	//Transformations
	Point4 ModelToView(const Matrix4& viewMtx, const Matrix4& modelMtx, const Matrix4& persepcMtx, const Point4& point);

	//Draw Objects
	void DrawObjects(int wWidth, int wHeight, bool drawLines, const Camera& mCam);

	static Camera cam;
};