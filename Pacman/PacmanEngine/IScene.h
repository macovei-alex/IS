#pragma once

#include "ISubject.h"
#include "IEvent.h"
#include <vector>

namespace pac
{
	/**
  * @enum SceneState
  * @brief Represents the state of the scene.
  */
	enum class SceneState
	{
		Playing,
		Won,
		Lost,
		WindowClosed
	};

	/**
  * @class IScene
  * @brief Interface for a game scene.
  */
	class IScene : public ISubject
	{
	public:
		/**
   * @brief Draws the scene.
   */
		virtual void Draw() const = 0;

		/**
   * @brief Advances the scene to the next tick.
   * @return The state of the scene after the tick.
   */
		virtual SceneState NextTick() = 0;

		/**
   * @brief Virtual destructor for IScene.
   */
		virtual ~IScene() = default;
	};
}
