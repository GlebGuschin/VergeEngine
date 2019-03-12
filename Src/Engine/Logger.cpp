#include "Logger.hpp"

namespace Verge3D {

//static const BufferSize = 1024;

const wchar_t* Logger::GetLogTypeString(LogType type) {

	switch (type) {

		case LogType::Error:
			return L"Error";
			break;

		case LogType::Info:
			return L"Info";
			break;

		case LogType::Warning:
			return L"Warning";
			break;

	};
	assert(0);

	return L"";
}

void Logger::log(LogType type, const String& message) {

	LogItem logItem;
	logItem.type = type;
	logItem.message = message;
	log(logItem);

}

/*
void Logger::log(LogType type, const wchar_t* format, ...) {

	wchar_t outputString[1024];
	va_list argList;

	va_start(argList, format);
	vswprintf_s(outputString, 1024, format, argList);
	va_end(argList);


	
}
*/

void Logger::log(const LogItem& logItem) {

	stream << "[" << GetLogTypeString(logItem.type) << "]  ";
	stream << logItem.message.w_str() << std::endl;
	stream.flush();

	/*
	stream << "[" << GetLogTypeString(type) << "]  ";
	stream << outputString << std::endl;
	stream.flush();
	*/
}

void Logger::info(const wchar_t* format, ...) {

	wchar_t outputString[1024];
	va_list argList;

	va_start(argList, format);
	vswprintf_s(outputString, 1024, format, argList);
	va_end(argList);

	log(LogType::Info, String(outputString));

}

void Logger::error(const wchar_t* format, ...) {

	wchar_t outputString[1024];
	va_list argList;

	va_start(argList, format);
	vswprintf_s(outputString, 1024, format, argList);
	va_end(argList);

	log(LogType::Error, String(outputString));

}

void Logger::warning(const wchar_t* format, ...) {

	wchar_t outputString[1024];
	va_list argList;

	va_start(argList, format);
	vswprintf_s(outputString, 1024, format, argList);
	va_end(argList);

	log(LogType::Warning, String(outputString));

}


void Logger::open(const char* fileName) {
	
	stream.open(fileName, std::ios::trunc | std::ios::out);
}

void Logger::close() {

	stream.close();

}


}