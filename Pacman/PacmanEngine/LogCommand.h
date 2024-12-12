#pragma once
#include <string>
#include "ICommand.h"
#include "Logger/Logger.h"

namespace pac
{
	class LogCommand : public ICommand
	{
	public:
		LogCommand(pac::Logger& logger, std::string_view message, pac::Logger::Level level);
		void execute() override;


	private:
		pac::Logger& mLogger;
		std::string_view mMessage;
		pac::Logger::Level mLevel;
	};
}
