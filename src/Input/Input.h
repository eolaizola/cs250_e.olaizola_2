#pragma once
#include "../cs250Parser.h"

namespace Input
{
	void UpdateInput();
	CS250Parser::Transform* GetObject(const std::string& name);
	void UpdateHierarchy(CS250Parser::Transform* obj);
};