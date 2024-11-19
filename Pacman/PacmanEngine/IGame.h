#pragma once


namespace pac
{
	class IGame
	{
	public:
		virtual void Run() = 0;
		virtual ~IGame() = default;
	};
}