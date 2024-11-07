#include "Logger.h"

#include <format>
#include <fstream>

namespace chr = std::chrono;


Logger Logger::cout(std::cout);


static std::string_view LogLevelToString(Logger::Level level)
{
	switch (level)
	{
	case Logger::Level::Debug:
		return "Debug";
	case Logger::Level::Info:
		return "Info";
	case Logger::Level::Warning:
		return "Warning";
	case Logger::Level::Error:
		return "Error";
	default:
		return "";
	}
}


static chr::time_point<chr::system_clock, chr::seconds> NowInSeconds()
{
	const auto now = chr::system_clock::now();
	return chr::time_point_cast<chr::seconds>(now);
}


Logger::Logger(std::ostream& os, Level minimumLevel)
	: mOutStream(os),
	mMinimumLevel(minimumLevel)
{
	/* empty */
}


Logger::Logger(std::string_view filename, Level minimumLevel)
	: mMinimumLevel(minimumLevel),
	mTempFileStream(std::string(filename), std::ios::trunc),
	mOutStream(mTempFileStream)
{
	/* empty */
}


void Logger::Log(std::string_view message, Level level)
{
	if ((int)level < (int)mMinimumLevel) {
		return;
	}

	mOutStream << std::format("({}) [{}]: {}\n",
		NowInSeconds(), LogLevelToString(level), message);
}
