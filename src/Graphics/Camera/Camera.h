#pragma once
#include "../src/MathLib/Matrix4.h"

enum CameraType
{
	STATIC = 0,
	FIRSTPERSON = 1,
	THIRDPERSON = 2
};
struct Camera
{
	void UpdateCamera();

	void GRMethodMatrix();
	void SetFirstPerson();
	void SetThirdPerson();

	Matrix4 mViewMatrix;

	bool mInit = false;
	Point4 mPos;
	Vector4 mView;
	Vector4 mUp;
	Vector4 mRight;

	CameraType type = STATIC;
};