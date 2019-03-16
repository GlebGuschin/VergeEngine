#include "Module.hpp"
#include "Framework.hpp"

namespace Verge3D {


void Module::info(const wchar_t* format, ...) {

	wchar_t outputString[1024];
	va_list argList;

	va_start(argList, format);
	vswprintf_s(outputString, 1024, format, argList);
	va_end(argList);
	
	getFramework()->getLogger()->info(outputString);

}

void Module::error(const wchar_t* format, ...) {

	wchar_t outputString[1024];
	va_list argList;

	va_start(argList, format);
	vswprintf_s(outputString, 1024, format, argList);
	va_end(argList);

	getFramework()->getLogger()->error(outputString);

}

void Module::warning(const wchar_t* format, ...) {

	wchar_t outputString[1024];
	va_list argList;

	va_start(argList, format);
	vswprintf_s(outputString, 1024, format, argList);
	va_end(argList);

	getFramework()->getLogger()->warning(outputString);

}
	

}
