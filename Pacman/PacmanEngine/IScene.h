#pragma once

#include "ISubject.h"


namespace pac
{
	class IScene : public ISubject
	{
		virtual void Draw() const = 0;
		virtual void NextTick() = 0;
	};
}
