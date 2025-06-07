#pragma once
#include <iostream>

class IEventListener
{
public:
	virtual void OnEventInvoked() = 0;
};