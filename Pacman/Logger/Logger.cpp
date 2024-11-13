#include "Logger.h"

#include <format>
#include <fstream>

namespace chr = std::chrono;


pac::Logger pac::Logger::cout(std::cout);


static std::string_view LogLevelToString(pac::Logger::Level level)
{
	switch (level)
	{
	case pac::Logger::Level::Debug:
		return "Debug";
	case pac::Logger::Level::Info:
		return "Info";
	case pac::Logger::Level::Warning:
		return "Warning";
	case pac::Logger::Level::Error:
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


pac::Logger::Logger(std::ostream& os, Level minimumLevel)
	: mOutStream(os),
	mMinimumLevel(minimumLevel)
{
	/* empty */
}


pac::Logger::Logger(std::string_view filename, Level minimumLevel)
	: mMinimumLevel(minimumLevel),
	mTempFileStream(std::string(filename), std::ios::trunc),
	mOutStream(mTempFileStream)
{
	/* empty */
}


void pac::Logger::Log(std::string_view message, Level level)
{
	if (level < mMinimumLevel) {
		return;
	}

	mOutStream << std::format("({}) [{}]: {}\n",
		NowInSeconds(), LogLevelToString(level), message);
}
