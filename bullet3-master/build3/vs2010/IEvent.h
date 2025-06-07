#pragma once
#include <iostream>

class IEvent
{
public:
	virtual void Invoke() = 0;
};