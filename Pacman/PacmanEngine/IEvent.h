#pragma once

#include <cstdint>
#include <array>
#include <string_view>
#include <stdexcept>
#include <format>


namespace pac
{
	enum class EventType : uint8_t
	{
		KeyPressed,
		PowerUp,
		SceneOver,
		_Count
	};

	inline std::string_view GetEventTypeName(EventType type)
	{
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

	class IEvent
	{
	public:
		virtual EventType GetType() const = 0;
		virtual ~IEvent() = default;
	};
}
