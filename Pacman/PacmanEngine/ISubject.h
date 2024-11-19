#pragma once

#include "IListener.h"


namespace pac
{
	class ISubject
	{
	public:
		virtual void AddListener(std::weak_ptr<IListener> listener, EventType eventType) = 0;
		virtual void RemoveListener(std::weak_ptr<IListener> listener, EventType eventType) = 0;
		virtual void Notify(IEvent* newEvent) const = 0;
		virtual ~ISubject() = default;
	};
}
