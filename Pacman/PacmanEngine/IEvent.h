#pragma once

#include "EventType.h"


namespace pac
{
	class IEvent
	{
	public:
		virtual EventType GetType() const = 0;
		virtual ~IEvent() = default;
	};
}
