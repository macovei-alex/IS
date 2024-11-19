#include "Logger.h"

#include <format>
#include <fstream>
#include <unordered_map>

namespace chr = std::chrono;


pac::Logger pac::Logger::cout(std::cout);


static std::string_view LogLevelToString(pac::Logger::Level level)
{
	static const std::unordered_map<pac::Logger::Level, std::string_view> levelStrings = {
		{ pac::Logger::Level::Debug, "Debug" },
		{ pac::Logger::Level::Info, "Info" },
		{ pac::Logger::Level::Warning, "Warn" },
		{ pac::Logger::Level::Error, "Error" }
	};

	return levelStrings.at(level);
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

	mOutStream << std::format("({}) [{}]:\t {}\n",
		NowInSeconds(), LogLevelToString(level), message);
}
