#pragma once


#include "Common.hpp"
#include "String.hpp"
#include "Module.hpp"


namespace Verge3D {


enum class FaceType : uint32_t { 
	NX, PX, NY, PY, NZ, PZ, Max
};


class TestModule : Module {

public:

	TestModule() : Module("TestModule") {}

};


/*

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

//class Logger : public Referenced {
class Logger {

	std::wfstream stream;
	DynamicArray<LogItem> items;

public:

	//Logger(const String&) : opened(false) {}

	Logger() {}
	~Logger() {}

	void log(LogType type, const wchar_t* format, ...);

	//virtual void open(const String&) {}
	//void log(LogType type, const String& moduleName, const String& message);	
	//void info(const wchar_t* moduleName, const wchar_t* format, ...);
	//void error(const wchar_t* moduleName, const wchar_t* format, ...);

	const DynamicArray<LogItem>& getItems() const { return items; };

	void open(const char*);
	void flush() {}
	//virtual void close() {}

	static const wchar_t*  GetLogTypeString(LogType);

};

*/

}