#pragma once
#include <functional>
#include <mutex>
#include <queue>

class EventBus {
public:
	using Event = std::function<void()>;
	static EventBus& GetInstance();
	void Post(Event e);
	void Dispatch();
private:
	std::mutex mtx;
	std::queue<Event> events;
};