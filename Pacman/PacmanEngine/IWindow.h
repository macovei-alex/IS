#pragma once

#include "Textures.h"
#include "Position.h"
#include "IEvent.h"
#include <string>
#include <vector>
#include <memory>

namespace pac
{
	/**
  * @class IWindow
  * @brief Interface for a game window.
  */
	class IWindow
	{
	public:
		/**
   * @brief Virtual destructor for IWindow.
   */
		virtual ~IWindow() = default;

		/**
   * @brief Draws the score on the window.
   * @param score The score to draw.
   */
		virtual void DrawScore(ScoreType score) = 0;

		/**
   * @brief Draws a texture at a specific position.
   * @param position The position to draw the texture.
   * @param texture The texture to draw.
   */
		virtual void DrawTexture(Position position, Textures texture) = 0;

		/**
   * @brief Checks if the window is open.
   * @return True if the window is open, false otherwise.
   */
		virtual bool IsOpen() const = 0;

		/**
   * @brief Checks if the window should close.
   * @return True if the window should close, false otherwise.
   */
		virtual bool ShouldClose() const = 0;

		/**
   * @brief Clears the window.
   */
		virtual void Clear() const = 0;

		/**
   * @brief Displays the contents of the window.
   */
		virtual void Display() = 0;

		/**
   * @brief Closes the window.
   */
		virtual void Close() = 0;

		/**
   * @brief Gets the events from the window.
   * @return A vector of unique pointers to events.
   */
		virtual std::vector<std::unique_ptr<IEvent>> GetEvents() = 0;
	};
}
