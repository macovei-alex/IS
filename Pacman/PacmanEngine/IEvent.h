#pragma once

#include <cstdint>


namespace pac
{
	enum class EventType : uint8_t
	{
		KeyPressed,
		PowerUp,
		SceneOver
	};


	class IEvent
	{
		virtual EventType GetType() const = 0;
	};
}
