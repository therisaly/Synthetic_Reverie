#pragma once
#include "IEvent.h"
#include "IEventListener.h"
#include <vector>
#include <unordered_set>

class Event : public IEvent
{
public:
	Event() {};
	void Invoke()
	{
		for (auto listener : listeners)
		{
			listener->OnEventInvoked();
		}
	}
	void Subscribe(IEventListener* listener)
	{
		listeners.insert(listener);
	}
	void Unsubscribe(IEventListener* listener)
	{
		listeners.erase(listener);
	}
protected:
	std::unordered_set<IEventListener*> listeners;
};