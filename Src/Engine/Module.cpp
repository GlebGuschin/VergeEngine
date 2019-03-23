#include "Module.hpp"
#include "Framework.hpp"

namespace Verge3D {

String MakeLogString(const String& name, const wchar_t* s) {
	String str;	
	str = String("(");
	str += String(name);
	str += String(") ");
	str += String(s);
	return str;
}

void Module::logInfo(const wchar_t* format, ...) {

	wchar_t outputString[1024];
	va_list argList;

	va_start(argList, format);
	vswprintf_s(outputString, 1024, format, argList);
	va_end(argList);
		
	getFramework()->getLogger()->info(MakeLogString(name,outputString).w_str());

}

void Module::logError(const wchar_t* format, ...) {

	wchar_t outputString[1024];
	va_list argList;

	va_start(argList, format);
	vswprintf_s(outputString, 1024, format, argList);
	va_end(argList);

	getFramework()->getLogger()->error(MakeLogString(name, outputString).w_str());

}

void Module::logWarning(const wchar_t* format, ...) {

	wchar_t outputString[1024];
	va_list argList;

	va_start(argList, format);
	vswprintf_s(outputString, 1024, format, argList);
	va_end(argList);

	getFramework()->getLogger()->warning(MakeLogString(name, outputString).w_str());

}
	

}
