#pragma once

#include "IEvent.h"
#include <memory>

namespace pac
{
	/**
  * @class IListener
  * @brief Interface for event listeners.
  */
	class IListener
	{
	public:
		/**
   * @brief Called when an event occurs.
   * @param event Pointer to the event that occurred.
   */
		virtual void OnEvent(const IEvent* event) = 0;

		/**
   * @brief Virtual destructor for IListener.
   */
		virtual ~IListener() = default;
	};
}
