#pragma once

#include "ISubject.h"
#include "IEvent.h"

#include <vector>


namespace pac
{
	enum class SceneState
	{
		Playing,
		Won,
		Lost,
		WindowClosed
	};

	class IScene : public ISubject
	{
	public:
		virtual void Draw() const = 0;
		virtual SceneState NextTick() = 0;
		virtual ~IScene() = default;
	};
}
