#pragma once

#include "EventType.h"

namespace pac
{
	/**
  * @class IEvent
  * @brief Interface for events.
  */
	class IEvent
	{
	public:
		/**
   * @brief Gets the type of the event.
   * @return The EventType of the event.
   */
		virtual EventType GetType() const = 0;

		/**
   * @brief Virtual destructor for IEvent.
   */
		virtual ~IEvent() = default;
	};
}
