#include "LogCommand.h"

pac::LogCommand::LogCommand(pac::Logger& logger, std::string_view message, pac::Logger::Level level) :
	mLogger{ logger },
	mMessage{ message },
	mLevel{ level }
{
}

void pac::LogCommand::execute()
{
	mLogger.Log(mMessage, mLevel);
}