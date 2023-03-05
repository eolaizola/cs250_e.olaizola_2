/* ---------------------------------------------------------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

Project: cs250_e.olaizola_2
Filename: Input.h

Author: Eritz 0laizola
Login: e.olaizola
StudentID:  540001219
Creation date: 02/05/2023
----------------------------------------------------------------------------------------------------------*/
#pragma once
#include "../Utils/cs250Parser.h"
#include "../src/Graphics/Camera/Camera.h"

/*
* 
* Namespace for the input
* 
*/
struct Input
{
	static Input& GetInstance()
	{
		static Input instance;
		return instance;
	}

	void UpdateInput(Camera& cam);
	CS250Parser::Transform* GetObject(const std::string& name);
	void UpdateHierarchy(CS250Parser::Transform* obj);
	void InitInput();

	bool mInitialzied = false;

	//Parts of the body
	CS250Parser::Transform* mBody = nullptr;
	CS250Parser::Transform* mTurret = nullptr;
	CS250Parser::Transform* mGun = nullptr;
	CS250Parser::Transform* mJoint = nullptr;
	CS250Parser::Transform* mWheel1 = nullptr;
	CS250Parser::Transform* mWheel2 = nullptr;
	CS250Parser::Transform* mWheel3 = nullptr;
	CS250Parser::Transform* mWheel4 = nullptr;
};