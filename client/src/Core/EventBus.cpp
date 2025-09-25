#include "EventBus.h"

EventBus &EventBus::GetInstance()
{
	static EventBus instance;
	return instance;
}

void EventBus::Subsribe(const std::string &event, Handler handler)
{
	handlers[event].push_back(std::move(handler));
}

void EventBus::Publish(const std::string &event, const std::string &data)
{
	if (handlers.find(event) != handlers.end())
	{
		for (auto &h : handlers[event])
		{
			h(data);
		}
	}
}