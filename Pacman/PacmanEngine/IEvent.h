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
	public:
		virtual EventType GetType() const = 0;
		virtual ~IEvent() = default;
	};
}
