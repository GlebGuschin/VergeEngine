//#include "stdafx.h"
#include "String.hpp"

namespace Verge3D {

const String String::Empty("");

String String::Format(const char* formatString, ...) {

	va_list argList;
	char outputString[1024 ];

	va_start( argList, formatString );
	vsprintf_s( outputString, strlen(outputString), formatString, argList );
	va_end( argList );
  
	String s(outputString);

	return s;
	
}

String String::Format(const wchar_t* formatString, ...) {

	wchar_t outputString[1024];

	
	va_list argList;

	va_start(argList, formatString);
	vswprintf_s(outputString, wcslen(outputString), formatString, argList);
	va_end(argList);
	
	size_t size = wcslen(outputString);

	outputString[size] = (wchar_t)0;

	return String( outputString );	
}

bool String::splitPathFileExt( String& path, String& file, String& ext, String& volume) const {
	
	const wchar_t* dotChar = L".";
	const wchar_t* slashChar = L"/";

	path = file = ext = L"";

	size_t dotPos = string.find_last_of(dotChar);
	size_t slashPos = string.find_last_of(slashChar);

	//if (dotPos == String::StringType::npos || slashPos == String::StringType::npos ) {

	if (dotPos != String::StringType::npos) {

		for (size_t i = dotPos + 1; i < string.size(); i++) {
			ext.string += string[i];			
		}
		//file.string = string;	
	} else {
		dotPos = string.size(); // hack
	}

	
	
	if (slashPos != String::StringType::npos) {

		for (size_t i = 0; i < slashPos; i++) {
			path.string += string[i];
		}

		for (size_t i = slashPos + 1; i < dotPos; i++) {
			file.string += string[i];
		}

	} else {

		for (size_t i = 0; i < dotPos; i++) {
			file.string += string[i];
		}


	}

	return true;
}


//void Split(const String& string, DynamicArray<String>& strings, wchar_t delimiter);

void String::split(DynamicArray<String>& strings, wchar_t delimiter) {

	bool b = false;
	strings.clear();
	String temp;

	for (size_t i = 0; i < string.size(); i++) {
		
		if ( string[i] == delimiter && temp.string.size() > 0 ) {
			strings.add( temp );
			temp = L"";
			b = true;
		} else {
			temp.string += string[i];
		}

	}

	if ( temp.string.size() > 0 ) {
		strings.add(temp);
		b = true;
	}

	//return b;
}

void String::replaceSlash() {

	for (size_t i = 0; i < string.size(); i++) {
		if ( string[ i ] == wchar_t('\\') ) {
			string[i] = wchar_t('/');
		}
	}
}

String::String(const wchar_t* string_) {
	size_t size = wcslen(string_);
	string.resize(size);
	for (size_t i = 0; i < size; i++) string[i] = string_[i];
}


String::String(const String& str) {

	string = str.string;
}

//bool StringisEqual(const String&) const;

}