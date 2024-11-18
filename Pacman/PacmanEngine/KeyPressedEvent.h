#pragma once

#include "IEvent.h"
#include "KeyCode.h"


namespace pac
{
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
