#pragma once

#include "IEvent.h"

namespace pac
{
	/**
  * @enum KeyCode
  * @brief Enum representing different key codes.
  */
	enum class KeyCode : uint8_t
	{
		Up,     ///< Up arrow key.
		Down,   ///< Down arrow key.
		Left,   ///< Left arrow key.
		Right,  ///< Right arrow key.
		W,      ///< W key.
		A,      ///< A key.
		S,      ///< S key.
		D,      ///< D key.
		Unknown ///< Unknown key.
	};

	/**
  * @class KeyPressedEvent
  * @brief Event representing a key press.
  */
	class KeyPressedEvent : public IEvent
	{
	public:
		/**
   * @brief Constructs a KeyPressedEvent.
   * @param keyCode The key code of the pressed key.
   */
		KeyPressedEvent(KeyCode keyCode) : mKeyCode(keyCode) { }

		/**
   * @brief Gets the type of the event.
   * @return The EventType of the event.
   */
		EventType GetType() const override { return EventType::KeyPressed; }

		/**
   * @brief Gets the key code of the pressed key.
   * @return The KeyCode of the pressed key.
   */
		KeyCode GetKeyCode() const { return mKeyCode; }

	private:
		KeyCode mKeyCode; ///< The key code of the pressed key.
	};
}
