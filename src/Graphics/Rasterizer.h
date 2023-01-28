#pragma once
#include "..\MathLib\Point4.h"

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

	//Draw Objects
	void DrawObjects(int wWidth, int wHeight);
};