#pragma once

#include "Textures.h"
#include "Position.h"

#include <string>

namespace pac
{
	class IWindow
	{
	public:
		//TODO: GetEvents when Events are implemented
		//virtual void GetEvents() = 0;
		virtual void DrawScore(const std::string& score) = 0;
		virtual void DrawTexture(Position position, pac::Textures texture) = 0;
		~IWindow() = default;
	};
}
