#pragma once

#include "ISubject.h"
#include "IEvent.h"

#include <vector>


namespace pac
{
	class IScene : public ISubject
	{
	public:
		virtual void Draw() const = 0;
		virtual void NextTick() = 0;
		virtual ~IScene() = default;
	};
}
