#include "Input.h"

#include "../cs250Parser.h"
#include <SFML/Graphics.hpp>

void Input::UpdateInput()
{
	sf::Clock clock;
	auto body = GetObject("body");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		auto wheel1 = GetObject("wheel1");
		auto wheel2 = GetObject("wheel2");
		auto wheel3 = GetObject("wheel3");
		auto wheel4 = GetObject("wheel4");


		Matrix4 roty;
		roty.RotationMatrix(1, body->rot.y, 1);
		
		Vector4 vec(0, 0, 1, 0);
		Matrix4 mtx;
		mtx.RotationMatrix(1,body->rot.y, 1);
		vec = mtx * vec;

		body->pos += vec * 0.3f;
		wheel1->rot.x += 0.5f;
		wheel2->rot.x += 0.5f;
		wheel3->rot.x += 0.5f;
		wheel4->rot.x += 0.5f;
		
		body->mTranslation.TranslationMatrix(body->pos.x, body->pos.y, body->pos.z);

		wheel1->mRotation.RotationMatrix(wheel1->rot.x, wheel1->rot.y, wheel1->rot.z);
		wheel2->mRotation.RotationMatrix(wheel2->rot.x, wheel2->rot.y, wheel2->rot.z);
		wheel3->mRotation.RotationMatrix(wheel3->rot.x, wheel3->rot.y, wheel3->rot.z);
		wheel4->mRotation.RotationMatrix(wheel4->rot.x, wheel4->rot.y, wheel4->rot.z);

		UpdateHierarchy(wheel1);
		UpdateHierarchy(wheel2);
		UpdateHierarchy(wheel3);
		UpdateHierarchy(wheel4);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		body->rot.y += 0.5f;

		body->mRotation.RotationMatrix(body->rot.x, body->rot.y, body->rot.z);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		body->rot.y -= 0.5f;

		body->mRotation.RotationMatrix(body->rot.x, body->rot.y, body->rot.z);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		auto turret = GetObject("turret");

		turret->rot.y += 0.5f;

		turret->mRotation.RotationMatrix(turret->rot.x, turret->rot.y, turret->rot.z);
		UpdateHierarchy(turret);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		auto turret = GetObject("turret");

		turret->rot.y -= 0.5f;

		turret->mRotation.RotationMatrix(turret->rot.x, turret->rot.y, turret->rot.z);
		UpdateHierarchy(turret);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		auto joint = GetObject("joint");

		joint->rot.x -= 0.5f;

		joint->mRotation.RotationMatrix(joint->rot.x, joint->rot.y, joint->rot.z);
		UpdateHierarchy(joint);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		auto joint = GetObject("joint");

		joint->rot.x += 0.5f;

		joint->mRotation.RotationMatrix(joint->rot.x, joint->rot.y, joint->rot.z);
		UpdateHierarchy(joint);
	}

	UpdateHierarchy(body);
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
	//obj->mTranslation.TranslationMatrix(obj->pos.x, obj->pos.y, obj->pos.z);

	obj->mSharedTransform = obj->mTranslation * obj->mRotation;
	obj->mWorldTransform = obj->mSharedTransform * obj->mScale;
}
