#pragma once
#include <string>
#include "ICommand.h"
#include "Logger/Logger.h"

namespace pac
{
	/**
  * @class LogCommand
  * @brief A command to log a message with a specified log level.
  */
	class LogCommand : public ICommand
	{
	public:
		/**
   * @brief Constructs a LogCommand.
   * @param logger Reference to a Logger object.
   * @param message The message to be logged.
   * @param level The log level for the message.
   */
		LogCommand(pac::Logger& logger, std::string_view message, pac::Logger::Level level);

	/**
   * @brief Executes the log command.
   */
		void execute() override;

	private:
		pac::Logger& mLogger; ///< Reference to the Logger object.
		std::string_view mMessage; ///< The message to be logged.
		pac::Logger::Level mLevel; ///< The log level for the message.
	};
}
