#pragma once
#include <functional>
#include <unordered_map>
#include <mutex>
#include <queue>
#include <string>

class EventBus
{
public:
	using Handler = std::function<void(const std::string &)>;
	static EventBus &GetInstance();
	void Subsribe(const std::string& event, Handler handler);
	void Publish(const std::string& event, const std::string& data);

private:
	EventBus() = default;
	EventBus(const EventBus &) = delete;
	EventBus(EventBus &&) = delete;

	std::mutex mtx;
	std::unordered_map<std::string, std::vector<Handler>> handlers;
};