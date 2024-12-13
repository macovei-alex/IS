#pragma once

#include "IListener.h"

namespace pac
{
	/**
  * @class ISubject
  * @brief Interface for subjects that notify listeners about events.
  */
	class ISubject
	{
	public:
		/**
   * @brief Adds a listener for a specific event type.
   * @param listener A weak pointer to the listener.
   * @param eventType The type of event the listener is interested in.
   */
		virtual void AddListener(std::weak_ptr<IListener> listener, EventType eventType) = 0;

		/**
   * @brief Removes a listener for a specific event type.
   * @param listener Pointer to the listener to be removed.
   * @param eventType The type of event the listener was interested in.
   */
		virtual void RemoveListener(const IListener* listener, EventType eventType) = 0;

		/**
   * @brief Notifies all listeners about a new event.
   * @param newEvent Pointer to the new event.
   */
		virtual void Notify(IEvent* newEvent) const = 0;

		/**
   * @brief Virtual destructor for ISubject.
   */
		virtual ~ISubject() = default;
	};
}
