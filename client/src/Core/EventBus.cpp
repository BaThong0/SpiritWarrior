#include "EventBus.h"

EventBus& EventBus::GetInstance()
{
	static EventBus instance;
	return instance;
}

void EventBus::Post(Event e)
{
	std::lock_guard<std::mutex> lock(mtx);
	events.push(std::move(e));
}

void EventBus::Dispatch()
{
	std::queue<Event> local;
	{
		std::lock_guard<std::mutex> lock(mtx);
		std::swap(local, events);
	}
	while (!local.empty()) {
		local.front()();
		local.pop();
	}
}
