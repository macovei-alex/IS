#include "EventType.h"

#include <string>
#include <stdexcept>
#include <format>
#include <unordered_map>


std::string_view pac::GetEventTypeName(EventType type)
{
	static const std::unordered_map<EventType, std::string_view> names = {
		{ EventType::KeyPressed, "KeyPressed" },
		{ EventType::PowerUp, "PowerUp" },
		{ EventType::SceneOver, "SceneOver" },
		{ EventType::WindowClosed, "WindowClosed" }
	};

	auto found = names.find(type);
	if (found == names.end())
	{
		throw std::runtime_error(std::format("Event type of index ( {} ) is not a valid event type", (size_t)type));
	}

	return found->second;
}
