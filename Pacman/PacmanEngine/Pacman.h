#pragma once
#include "GameObject.h"

namespace pac
{
	class Pacman : public GameObject
	{
	public:
		Pacman();
		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();
	private:
	};
}