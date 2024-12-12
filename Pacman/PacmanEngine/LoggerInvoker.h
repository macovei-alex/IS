#pragma once
#include <memory>
#include "ICommand.h"

class LoggerInvoker
{
public:
	void setCommand(std::unique_ptr<ICommand> command);

	void executeCommand();
private:
	std::unique_ptr<ICommand> mCommand;
};