#include "Engine.hpp"
#include "World.hpp"

#include <Windows.h>

namespace Verge3D {

void DebugLog(const char* format, ...) {

#ifdef _DEBUG

	va_list argList;
	char outputString[4096];

	va_start(argList, format);
	vsprintf_s(outputString, sizeof(outputString), format, argList);
	va_end(argList);

	OutputDebugStringA(outputString);
	OutputDebugStringA("\n");

#endif

}

}