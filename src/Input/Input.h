#pragma once
#include "../Utils/cs250Parser.h"

namespace Input
{
	void UpdateInput();
	CS250Parser::Transform* GetObject(const std::string& name);
	void UpdateHierarchy(CS250Parser::Transform* obj);
	void InitInput();

	static bool mInitialzied = false;

	static CS250Parser::Transform* mBody;
	static CS250Parser::Transform* mTurret;
	static CS250Parser::Transform* mGun;
	static CS250Parser::Transform* mJoint;
	static CS250Parser::Transform* mWheel1;
	static CS250Parser::Transform* mWheel2;
	static CS250Parser::Transform* mWheel3;
	static CS250Parser::Transform* mWheel4;
};