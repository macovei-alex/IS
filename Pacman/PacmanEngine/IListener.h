#pragma once

#include "IEvent.h"

#include <memory>


namespace pac
{
	class IListener
	{
	public:
		virtual void OnEvent(std::shared_ptr<IEvent> event) = 0;
		virtual ~IListener() = default;
	};
}
