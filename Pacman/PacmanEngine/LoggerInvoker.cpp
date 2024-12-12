#include "LoggerInvoker.h"

void LoggerInvoker::setCommand(std::unique_ptr<ICommand> command)
{
	mCommand = std::move(command);
}

void LoggerInvoker::executeCommand()
{
	if (mCommand)
	{
		mCommand->execute();
	}
}
