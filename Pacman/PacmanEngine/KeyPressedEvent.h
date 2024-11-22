#pragma once

#include "IEvent.h"


namespace pac
{
	enum class KeyCode : uint8_t
	{
		Up,
		Down,
		Left,
		Right,
		W,
		A,
		S,
		D,
		Unknown
	};

	class KeyPressedEvent : public IEvent
	{
	public:
		KeyPressedEvent(KeyCode keyCode) : mKeyCode(keyCode) { }
		EventType GetType() const override { return EventType::KeyPressed; }
		KeyCode GetKeyCode() const { return mKeyCode; }

	private:
		KeyCode mKeyCode;
	};
}
