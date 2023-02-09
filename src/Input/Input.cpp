#include "Input.h"
#include "../MathLib/Matrix4.h"
#include <SFML/Graphics.hpp>

void Input::UpdateInput()
{
	if(!mInitialzied)
	{
		//Initialize one time
		//To not search them all the time
		InitInput();
		mInitialzied = true;
	}

	sf::Clock clock;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Matrix4 roty;
		roty.RotationMatrix(1, mBody->rot.y, 1);
		
		Vector4 vec(0, 0, 1, 0);
		Matrix4 mtx;
		mtx.RotationMatrix(1,mBody->rot.y, 1);
		vec = mtx * vec;

		mBody->pos += vec * 0.4f;
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
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		mBody->rot.y += 0.5f;

		mBody->mRotation.RotationMatrix(mBody->rot.x, mBody->rot.y, mBody->rot.z);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		mBody->rot.y -= 0.5f;

		mBody->mRotation.RotationMatrix(mBody->rot.x, mBody->rot.y, mBody->rot.z);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		mTurret->rot.y += 0.5f;

		mTurret->mRotation.RotationMatrix(mTurret->rot.x, mTurret->rot.y, mTurret->rot.z);
		UpdateHierarchy(mTurret);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		mTurret->rot.y -= 0.5f;

		mTurret->mRotation.RotationMatrix(mTurret->rot.x, mTurret->rot.y, mTurret->rot.z);
		UpdateHierarchy(mTurret);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		mJoint->rot.x -= 0.5f;

		mJoint->mRotation.RotationMatrix(mJoint->rot.x, mJoint->rot.y, mJoint->rot.z);
		UpdateHierarchy(mJoint);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		mJoint->rot.x += 0.5f;

		mJoint->mRotation.RotationMatrix(mJoint->rot.x, mJoint->rot.y, mJoint->rot.z);
		UpdateHierarchy(mJoint);
	}

	UpdateHierarchy(mBody);
	CS250Parser::UpdateObjects();
}

CS250Parser::Transform* Input::GetObject(const std::string& name)
{
	for(auto it = CS250Parser::objects.begin(); it != CS250Parser::objects.end(); it++)
	{
		if ((*it).name == name)
			return &(*it);
	}
	return nullptr;
}

void Input::UpdateHierarchy(CS250Parser::Transform* obj)
{
	if (!obj)
		return;

	obj->mSharedTransform = obj->mTranslation * obj->mRotation;
	obj->mWorldTransform = obj->mSharedTransform * obj->mScale;
}

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
}
