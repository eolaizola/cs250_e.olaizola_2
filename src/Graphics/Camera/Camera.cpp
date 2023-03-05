#include "Camera.h"
#include "../src/Utils/cs250Parser.h"
#include "../src/Input/Input.h"
#include "../src/MathLib/MathUtilities.h"
#include <iostream>

void Camera::UpdateCamera()
{
	switch (type)
	{
	case STATIC:
		{
			mPos = CS250Parser::position;
			mUp = CS250Parser::up;
			mView = CS250Parser::view;
			break;
		}
	
	case FIRSTPERSON:
		{
			SetFirstPerson();
			break;
		}
	case THIRDPERSON:
		{
			SetThirdPerson();
			break;
		}
	}
	GRMethodMatrix();
}

void Camera::GRMethodMatrix()
{
	//General Rotation Method for -z axis
	Vector4 v = mView;
	Vector4 up = mUp;
	Point4 cop = mPos;

	Matrix4 mT;
	Matrix4 mRotY;
	Matrix4 mRotX;
	Matrix4 mRotZ;

	mT.Identity();
	mRotY.Identity();
	mRotX.Identity();
	mRotZ.Identity();

	mT.TranslationMatrix(-cop.x, -cop.y, -cop.z);

	float mLength = sqrtf(v.x * v.x + v.z * v.z);

	mRotY.m[0][0] = -v.z / mLength;
	mRotY.m[0][2] = v.x / mLength;
	mRotY.m[2][0] = -v.x / mLength;
	mRotY.m[2][2] = -v.z / mLength;

	float mLength2 = v.Length();

	mRotX.m[1][1] = mLength / mLength2;
	mRotX.m[1][2] = v.y / mLength2;
	mRotX.m[2][1] = -v.y / mLength2;
	mRotX.m[2][2] = mLength / mLength2;

	Vector4 upPrime = mRotX * mRotY * mT * up;
	float mLengthUp = sqrtf(upPrime.x * upPrime.x + upPrime.y * upPrime.y);

	mRotZ.m[0][0] = upPrime.y / mLengthUp;
	mRotZ.m[0][1] = -upPrime.x / mLengthUp;
	mRotZ.m[1][0] = upPrime.x / mLengthUp;
	mRotZ.m[1][1] = upPrime.y / mLengthUp;

	Vector4 fdf = mRotZ * up;
	Matrix4 mPain = mRotY * mT;

	mPain = mRotX * mPain;
	mPain = mRotZ * mPain;

	Matrix4 m = mRotZ * mRotX * mRotY * mT;
	mViewMatrix = mRotZ * mRotX * mRotY * mT;
}

void Camera::SetFirstPerson()
{
	Vector4 yaxis(0, 1, 0, 0);

	//Compute the first person
	mPos = Input::GetInstance().mTurret->pos;
	mView = Input::GetInstance().mTurret->mForward;

	mUp = yaxis;

	mRight = mView.Cross(mUp);
}

void Camera::SetThirdPerson()
{
	Vector4 yaxis(0, 1, 0, 0);
	float height = CS250Parser::height;
	float distance = CS250Parser::distance;
	auto tank = Input::GetInstance().mBody;

	mPos = tank->pos - tank->mForward * distance + yaxis * height;
	float mLength = (tank->pos - mPos).Length();

	mView = (tank->pos - mPos) / mLength;

	mRight = mView.Cross(yaxis);
	mUp = mRight.Cross(mView);
}