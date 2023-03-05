/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

Project: cs250_e.olaizola_2
Filename: Input.cpp

Author: Eritz 0laizola
Login: e.olaizola
StudentID:  540001219
Creation date: 02/05/2023
----------------------------------------------------------------------------------------------------------*/

#include "Input.h"
#include "../MathLib/Matrix4.h"
#include "../Graphics/Camera/Camera.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/*
*
* \brief Updates the objects depending on the input
*
*/
void Input::UpdateInput(Camera& cam)
{
	if (!mInitialzied)
	{
		//Initialize one time
		//To not search them all the time
		InitInput();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		cam.type = CameraType::STATIC;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		cam.type = CameraType::FIRSTPERSON;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		cam.type = CameraType::THIRDPERSON;

	if (cam.type == CameraType::THIRDPERSON)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			if ((CS250Parser::distance - 1) >= 100)
				CS250Parser::distance -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			if ((CS250Parser::distance + 1) <= 200)
				CS250Parser::distance += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			if ((CS250Parser::height - 1) >= 0)
				CS250Parser::height -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			if ((CS250Parser::height + 1) <= 100)
				CS250Parser::height += 1;
		}
	}

	//Controls of the tank.
	//No much comment because its straightforward

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Vector4 vec(0, 0, 1, 0);
		Matrix4 mtx;
		mtx.RotationMatrix(mBody->rot.x, mBody->rot.y, mBody->rot.z);
		mBody->mForward = mtx * vec;

		mBody->pos += mBody->mForward * 0.5f;
		mWheel1->rot.x += 0.5f;
		mWheel2->rot.x += 0.5f;
		mWheel3->rot.x += 0.5f;
		mWheel4->rot.x += 0.5f;

		mBody->mTranslation.TranslationMatrix(mBody->pos.x, mBody->pos.y, mBody->pos.z);

		mWheel1->mRotation.RotationMatrix(mWheel1->rot.x, mWheel1->rot.y, mWheel1->rot.z);
		mWheel2->mRotation.RotationMatrix(mWheel2->rot.x, mWheel2->rot.y, mWheel2->rot.z);
		mWheel3->mRotation.RotationMatrix(mWheel3->rot.x, mWheel3->rot.y, mWheel3->rot.z);
		mWheel4->mRotation.RotationMatrix(mWheel4->rot.x, mWheel4->rot.y, mWheel4->rot.z);

		UpdateHierarchy(mWheel1);
		UpdateHierarchy(mWheel2);
		UpdateHierarchy(mWheel3);
		UpdateHierarchy(mWheel4);
		UpdateHierarchy(mBody);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Vector4 vec(0, 0, 1, 0);
		Matrix4 mtx;
		mtx.RotationMatrix(mBody->rot.x, mBody->rot.y, mBody->rot.z);
		mBody->mForward = mtx * vec;

		mBody->rot.y += 0.5f;

		mBody->mRotation.RotationMatrix(mBody->rot.x, mBody->rot.y, mBody->rot.z);
		UpdateHierarchy(mBody);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Vector4 vec(0, 0, 1, 0);
		Matrix4 mtx;
		mtx.RotationMatrix(mBody->rot.x, mBody->rot.y, mBody->rot.z);
		mBody->mForward = mtx * vec;

		mBody->rot.y -= 0.5f;

		mBody->mRotation.RotationMatrix(mBody->rot.x, mBody->rot.y, mBody->rot.z);
		UpdateHierarchy(mBody);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		mTurret->rot.y += 0.5f;

		mTurret->mRotation.RotationMatrix(mTurret->rot.x, mTurret->rot.y, mTurret->rot.z);
		UpdateHierarchy(mTurret);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		mTurret->rot.y -= 0.5f;

		mTurret->mRotation.RotationMatrix(mTurret->rot.x, mTurret->rot.y, mTurret->rot.z);
		UpdateHierarchy(mTurret);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		mJoint->rot.x -= 0.5f;

		mJoint->mRotation.RotationMatrix(mJoint->rot.x, mJoint->rot.y, mJoint->rot.z);
		UpdateHierarchy(mJoint);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		mJoint->rot.x += 0.5f;

		mJoint->mRotation.RotationMatrix(mJoint->rot.x, mJoint->rot.y, mJoint->rot.z);
		UpdateHierarchy(mJoint);
	}
	CS250Parser::UpdateObjects();
}

/*
*
* \brief Return the object, find object by name
*
*/
CS250Parser::Transform* Input::GetObject(const std::string& name)
{
	for (auto it = CS250Parser::objects.begin(); it != CS250Parser::objects.end(); it++)
	{
		if ((*it).name == name)
			return &(*it);
	}
	return nullptr;
}

/*
*
* \brief If an input change an object, this will update its hierarchy
*
*/
void Input::UpdateHierarchy(CS250Parser::Transform* obj)
{
	if (!obj)
		return;

	obj->mSharedTransform = obj->mTranslation * obj->mRotation;
	obj->mWorldTransform = obj->mSharedTransform * obj->mScale;
}

/*
*
* \brief Initilize the object for the input
*
*/
void Input::InitInput()
{
	mBody = GetObject("body");
	mTurret = GetObject("turret");
	mGun = GetObject("gun");
	mJoint = GetObject("joint");
	mWheel1 = GetObject("wheel1");
	mWheel2 = GetObject("wheel2");
	mWheel3 = GetObject("wheel3");
	mWheel4 = GetObject("wheel4");

	mBody->mForward = Vector4(0, 0, 1, 0);
	mInitialzied = true;
}
	