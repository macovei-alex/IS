#pragma once

#include "IListener.h"


namespace pac
{
	class ISubject
	{
	public:
		virtual void AddListener(std::shared_ptr<IListener> listener, EventType eventType) = 0;
		virtual void RemoveListener(std::shared_ptr<IListener> listener, EventType eventType) = 0;
		virtual void Notify(std::shared_ptr<IEvent> newEvent) const = 0;
		virtual ~ISubject() = default;
	};
}
