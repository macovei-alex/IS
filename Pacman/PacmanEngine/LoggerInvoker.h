#pragma once
#include <memory>
#include "ICommand.h"

/**
 * @class LoggerInvoker
 * @brief Invokes commands to log messages.
 */
class LoggerInvoker
{
public:
	/**
  * @brief Sets the command to be executed.
  * @param command A unique pointer to the command.
  */
	void setCommand(std::unique_ptr<ICommand> command);

	/**
  * @brief Executes the set command.
  */
	void executeCommand();
private:
	std::unique_ptr<ICommand> mCommand; ///< The command to be executed.
};