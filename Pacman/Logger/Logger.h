#pragma once

#include <iostream>
#include <fstream>
#include <string_view>
#include <string>
#include <chrono>


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

public:
	static Logger cout;

private:
	std::ostream& mOutStream;
	std::ofstream mTempFileStream;
	Level mMinimumLevel;
};
