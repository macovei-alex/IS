#include "EventType.h"

#include <string>
#include <array>
#include <stdexcept>
#include <format>


std::string_view pac::GetEventTypeName(EventType type) {
	static const std::array<std::string, static_cast<size_t>(EventType::_Count)> names = {
		"KeyPressed",
		"PowerUp",
		"SceneOver",
	};

	size_t typeIndex = static_cast<size_t>(type);
	if (typeIndex >= names.size())
	{
		throw std::runtime_error(std::format("Event type of index ( {} ) is not a valid event type", typeIndex));
	}

	return names[typeIndex];
}
