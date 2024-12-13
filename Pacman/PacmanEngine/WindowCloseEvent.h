#pragma once

#include "IEvent.h"

namespace pac
{
	/**
  * @class WindowCloseEvent
  * @brief Event representing a window close action.
  */
	class WindowCloseEvent : public IEvent
	{
	public:
		/**
   * @brief Gets the type of the event.
   * @return The EventType of the event.
   */
		EventType GetType() const override { return EventType::WindowClose; }
	};
}
