#pragma once

#include "Common.hpp"
#include "String.hpp"

namespace Verge3D {

enum LogType : uint32_t {
	Info,
	Error,
	Warning
};


class LoggerListener {
public:
	//virtual void 
};

struct LogItem {
	LogType type;
	String message;
};


//class Logger {
class Logger : public Referenceable {

	std::wfstream stream;
	DynamicArray<LogItem> items;

	void log(const LogItem&);

public:

	//Logger(const String&) : opened(false) {}

	Logger() {}
	~Logger() {}

	void log(LogType type, const wchar_t* format, ...);
	void log(LogType type, const String&);
	
	void info(const wchar_t* format, ...);
	void error(const wchar_t* format, ...);
	void warning(const wchar_t* format, ...);
	

	//virtual void open(const String&) {}
	//void log(LogType type, const String& moduleName, const String& message);	
	
	const DynamicArray<LogItem>& getItems() const { return items; };

	void open(const char*);
	void flush() {}
	void close();

	static const wchar_t*  GetLogTypeString(LogType);

};

}