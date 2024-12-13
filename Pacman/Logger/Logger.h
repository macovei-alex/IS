#pragma once
#pragma once

#include <iostream>
#include <fstream>
#include <string_view>
#include <string>
#include <chrono>
#include <memory>
#include <mutex>

namespace pac
{
	/**
  * @brief A class for logging messages with different severity levels.
  */
	class Logger
	{
	public:
		/**
   * @brief Enum representing the log levels.
   */
		enum class Level {
			Debug,   ///< Debug level
			Info,    ///< Info level
			Warning, ///< Warning level
			Error    ///< Error level
		};

	public:
		/**
   * @brief Constructs a Logger object that logs to the given output stream.
   * 
   * @param os The output stream to log to.
   * @param minimumLevel The minimum log level to log.
   */
		Logger(std::ostream& os, Level minimumLevel = Level::Debug);

		/**
   * @brief Constructs a Logger object that logs to the given file.
   * 
   * @param filename The name of the file to log to.
   * @param minimumLevel The minimum log level to log.
   */
		Logger(std::string_view filename, Level minimumLevel = Level::Debug);

		/**
   * @brief Logs a message with the given log level.
   * 
   * @param message The message to log.
   * @param level The log level of the message.
   */
		void Log(std::string_view message, Level level);

		/**
   * @brief Logs a debug message.
   * 
   * @param message The debug message to log.
   */
		inline void Debug(std::string_view message) { Log(message, Level::Debug); }

		/**
   * @brief Logs an info message.
   * 
   * @param message The info message to log.
   */
		inline void Info(std::string_view message) { Log(message, Level::Info); }

		/**
   * @brief Logs a warning message.
   * 
   * @param message The warning message to log.
   */
#include <iostream>
#include <fstream>
#include <string_view>
#include <string>
#include <chrono>
#include <memory>
#include <mutex>

namespace pac
{
	class Logger
	{
	public:
		enum class Level {
			Debug,
			Info,
			Warning,
			Error
		};

	public:
		Logger(std::ostream& os, Level minimumLevel = Level::Debug);
		Logger(std::string_view filename, Level minimumLevel = Level::Debug);

		void Log(std::string_view message, Level level);

		inline void Debug(std::string_view message) { Log(message, Level::Debug); }
		inline void Info(std::string_view message) { Log(message, Level::Info); }
		inline void Warning(std::string_view message) { Log(message, Level::Warning); }
		inline void Error(std::string_view message) { Log(message, Level::Error); }

		inline void SetMinimumLogLevel(Level level) { mMinimumLevel = level; }

		static Logger& GetInstance(std::ostream& os = std::cout, Level minimumLevel = Level::Debug)
		{
			static Logger instance(os, minimumLevel);
			return instance;
		}

	private:
		std::ostream& mOutStream;
		std::ofstream mTempFileStream;
		Level mMinimumLevel;

		// Delete copy constructor and assignment operator to prevent copying
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;
	};
}
