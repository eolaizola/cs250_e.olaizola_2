#include "Rasterizer.h"
#include "..\MathLib/MathUtilities.h"
#include "..\FrameBuffer.h"
#include "..\cs250Parser.h"

void Rasterizer::DrawLine(const Point4& p1, const Point4& p2, const Color col)
{
	//Change rate
	int dx = Utils::Round(p2.x) - Utils::Round(p1.x);
	int dy = Utils::Round(p2.y) - Utils::Round(p1.y);

	if (dx == 0)
	{
		DrawVerticalLine(p1, p2, col);
		return;
	}
	else if (dy == 0)
	{
		DrawHorizontalLine(p1, p2, col);
		return;
	}
	else if (abs(dx) == abs(dy))
	{
		DrawDiagonalLine(p1, p2, col);
		return;
	}

	int m = dy / dx;

	int dirx = dx > 0 ? 1 : -1;
	int diry = dy > 0 ? 1 : -1;

	//Initial decision parameter
	int initial_DP_1 = 2 * (abs(dy)) - abs(dx);
	int initial_DP_2 = 2 * (abs(dx)) - abs(dy);

	//Change coordinate when abs(m) < 1
	int coordinate_1_1 = 2 * (abs(dy));//1 change
	int coordinate_1_2 = 2 * (abs(dy)) - 2 * (abs(dx));//2 change

	//Change coordinate when abs(m) > 1
	int coordinate_2_1 = 2 * (abs(dx));//1 change
	int coordinate_2_2 = 2 * (abs(dx)) - 2 * (abs(dy));//2 change

	if (abs(m) < 1)
	{
		int x = Utils::Round(p1.x);
		int y = Utils::Round(p1.y);

		int x2 = Utils::Round(p2.x);
		int y2 = Utils::Round(p2.y);

		while (x != x2)
		{

			FrameBuffer::SetPixel(x, y, col.r, col.g, col.b);
			//Change 2 coordinates
			if (initial_DP_1 > 0)
			{
				x += dirx;
				y += diry;
				//Update the decision parameter
				initial_DP_1 += coordinate_1_2;
			}
			//Change 1 ccordinate
			else
			{
				x += dirx;
				//Update the decision parameter
				initial_DP_1 += coordinate_1_1;
			}
		}
	}
	
	else
	{
		int x = Utils::Round(p1.x);
		int y = Utils::Round(p1.y);

		int x2 = Utils::Round(p2.x);
		int y2 = Utils::Round(p2.y);

		while (y != y2)
		{
			FrameBuffer::SetPixel(x, y, col.r, col.g, col.b);
			//Change 2 coordinates
			if (initial_DP_2 > 0)
			{
				x += dirx;
				y += diry;
				//Update the decision parameter
				initial_DP_2 += coordinate_2_2;
			}
			//Change 1 coordinate
			else
			{
				y += diry;
				//Update the decision parameter
				initial_DP_2 += coordinate_2_1;
			}
		}
	}
}

void Rasterizer::DrawVerticalLine(const Point4& p1, const Point4& p2, const Color col)
{
	unsigned int y_start = p1.y;
	unsigned int y_end = p2.y;
	//Direction to be drawn
	unsigned int dir = (p1.y - p2.y) > 0 ? -1 : +1;

	while (Utils::Round(y_start) != Utils::Round(y_end))
	{
		FrameBuffer::SetPixel(p1.x, y_start, col.r, col.g, col.b);
		y_start += dir;
	}
}

void Rasterizer::DrawHorizontalLine(const Point4& p1, const Point4& p2, const Color col)
{
	unsigned int x_start = p1.x;
	unsigned int x_end = p2.x;
	//Direction to be drawn
	unsigned int dir = (p1.x - p2.x) > 0 ? -1 : +1;

	while (Utils::Round(x_start) != Utils::Round(x_end))
	{
		FrameBuffer::SetPixel(x_start, p1.y, col.r, col.g, col.b);
		x_start += dir;
	}
}

void Rasterizer::DrawDiagonalLine(const Point4& p1, const Point4& p2, const Color col)
{
	unsigned int x_start = p1.x;
	unsigned int y_start = p1.y;
	unsigned int x_end = p2.x;
	//Direction to be drawn x and y
	unsigned int dir_x = (p1.x - p2.x) > 0 ? -1 : +1;
	unsigned int dir_y = (p1.y - p2.y) > 0 ? -1 : +1;

	while (Utils::Round(x_start) != Utils::Round(x_end))
	{
		FrameBuffer::SetPixel(x_start, y_start, col.r, col.g, col.b);
		x_start += dir_x;
		y_start += dir_y;
	}
}

void Rasterizer::DrawObjects(int wWidth, int wHeight)
{
	Color col(0,0,0);

	Matrix4 rot;
	Matrix4 mtx;
	Matrix4 scale;
	Matrix4 trans;

	Matrix4 pers;
	Matrix4 view;

	rot.Identity();
	scale.Identity();
	trans.Identity();

	pers = CS250Parser::GetPerspectiveMatrix();
	view = CS250Parser::GetViewportMatrix(wWidth, wHeight);

	Point4 point1;
	Point4 point2;
	Point4 point3;

	auto shap = CS250Parser::shapes.begin();
	auto obj = CS250Parser::objects.begin();

	for(; shap != CS250Parser::shapes.end(); shap++, obj++)
	{
		mtx.Identity();

		//Take the transform matrix of the object
		scale.ScaleMatrix((*obj).sca.x, (*obj).sca.y, (*obj).sca.z);
		trans.TranslationMatrix((*obj).pos.x, (*obj).pos.y, (*obj).pos.z);

		mtx = trans * rot * scale;

		int j = 0;
		for(auto it = (*shap).faces.begin(); it != (*shap).faces.end(); it++, j++)
		{
			point1 = (*shap).vertices[(*it).indices[0]];
			point2 = (*shap).vertices[(*it).indices[1]];
			point3 = (*shap).vertices[(*it).indices[2]];

			point1 = ModelToView(view, mtx, pers, point1);
			point2 = ModelToView(view, mtx, pers, point2);
			point3 = ModelToView(view, mtx, pers, point3);

			col.r = (*shap).colors[j].r;
			col.g = (*shap).colors[j].g;
			col.b = (*shap).colors[j].b;

			DrawLine(point1, point2, col);
			DrawLine(point2, point3, col);
			DrawLine(point3, point1, col);
		}
	}
}


Point4 Rasterizer::ModelToView(const Matrix4& viewMtx, const Matrix4& modelMtx, const Matrix4& persepcMtx, const Point4& point)
{
	Point4 mPoint;
	//Model to world
	mPoint = modelMtx * point;
	
	//World to perspective
	mPoint = (persepcMtx * mPoint) / (-mPoint.z);
	
	mPoint = viewMtx * mPoint;

	return mPoint;
}