#pragma once

#include "DynamicArray.hpp"

namespace Verge3D {

class String;

class String { 

	typedef std::wstring StringType;

	StringType string;

public:

	String() {}	
	~String() {}
	//String( const wchar_t* string_ ) : string( string_) {}
	String(const wchar_t* string_);

	String(const String&);
	/*
	String(const wchar_t* format, ...)  {

		wchar_t outputString[1024];

		va_list argList;

		va_start(argList, format);

		vswprintf_s(outputString, sizeof(outputString), format, argList);
		va_end(argList);
		
		string = outputString;
	}*/

	String( const char* string_ ) {

		size_t size = strlen(string_);
		string.resize(size);

		for (size_t i = 0; i < size; i++) { 
			string[i] = (wchar_t)string_[i];		
		}

	}

	bool splitPathFileExt( String& path, String& file, String& ext, String& volume) const;
	void split(DynamicArray<String>& strings, wchar_t delimiter);
	void replaceSlash();

	static String Format(const char* formatString, ...);
	static String Format(const wchar_t* formatString, ...);

	static const String Empty;	

	//

	//AssetName( const wchar_t* name_ ) { name.reserve( MAX_Asset_NAME_SIZE ); name = name_; }
	//AssetName( const AssetName& name_ ) { name = name_.name; }
	//~AssetName() {}

	bool operator==( const String& rhs ) const { return( string == rhs.string ); }
	bool operator!=( const String& rhs ) const { return( string != rhs.string ); }
	bool operator<(const String& rhs) const { return(std::lexicographical_compare(string.begin(), string.end(), rhs.string.begin(), rhs.string.end())); }

	String& operator+=(const String& rhs) {  string+= rhs.string; return *this; }

	//static AssetName NONAME;

	//const  StringType& w_str() const { return string; }
	const wchar_t* w_str() const { return string.c_str(); }

private:

};


class FileName {

	String path, file, ext, name, volume;
	bool valid;
	bool local;

	
public:

	FileName() : valid(false) {}

	FileName( const char* cstr ) {	
		
		String string(cstr);
		valid = string.splitPathFileExt( path, file, ext, volume );			
		name = string;
		
	}

	FileName( const String& string ) {	
		valid = string.splitPathFileExt( path, file, ext, volume);
		name = string;
	}

	bool isValid() const { return valid; }
	bool isLocal() const { return local; }

	const String& getName() const { return name; }
	const String& getPath() const { return path; }
	const String& getFile() const { return file; }
	const String& getExt() const { return ext; }

	bool operator<(const FileName& rhs) const { return( name < rhs.name); }

};


}
