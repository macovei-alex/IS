#pragma once

#include <cstdint>
#include <string_view>

namespace pac
{
	/**
  * @enum EventType
  * @brief Enum representing different types of events.
  */
	enum class EventType : uint8_t
	{
		KeyPressed, ///< Event for key press.
		WindowClose ///< Event for window close.
	};

	/**
  * @brief Converts an EventType to its string representation.
  * @param type The EventType to convert.
  * @return A string view representing the EventType.
  */
	std::string_view EventTypeToStr(EventType type);
}
