#pragma once
#include "IEventListener.h"

class LevelsIterator : public IEventListener
{
public:
	LevelsIterator()
	{
		iterator = 0;
	}
	void OnEventInvoked() override
	{
		iterator++;
	}
	int GetIterator()
	{
		return iterator;
	}
private:
	int iterator;
};