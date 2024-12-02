#pragma once

#include <cstdint>
#include <string_view>


namespace pac
{
	enum class EventType : uint8_t
	{
		KeyPressed,
		WindowClose
	};

	std::string_view EventTypeToStr(EventType type);
}
