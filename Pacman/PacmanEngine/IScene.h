#pragma once

#include "ISubject.h"


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
