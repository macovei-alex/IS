#pragma once

#include "IEvent.h"


namespace pac
{
	class WindowCloseEvent : public IEvent
	{
	public:
		EventType GetType() const override { return EventType::WindowClose; }
	};
}
