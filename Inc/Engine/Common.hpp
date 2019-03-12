
#pragma once


#include <typeinfo.h>
#include <string>
#include <wchar.h>
#include <assert.h>
#include <crtdbg.h>
#include <stdio.h>
#include <tchar.h>
#include <cstdarg>
#include <cstdlib>
#include <cmath>
#include <limits>



#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <algorithm>

namespace Verge3D {

/*
typedef unsigned uint;
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned int dword;
typedef unsigned short word;
typedef unsigned	uint32;
typedef int			int32;

typedef unsigned short  uint16;
typedef short 	int16;

typedef unsigned char uint8;
typedef char int8;

typedef unsigned long long uint64;
typedef  long long 			int64;
*/


class String;
class Name;
class Module;
class Framework;

class Entity;
class World;
class Component;



class Referenceable {

	volatile unsigned counter;

	//volatile DWORD counter;

public:

	Referenceable() : counter(0) {}
	virtual ~Referenceable() {}

	void addRef() { 
		counter++; 
	}
	
	void removeRef() { 
		assert(counter); 
		if (counter == 1) { 
			counter = 0; 
			delete this; 
		} else { 
			counter--; 
		} 
	}
	
	unsigned getCounter() const { return(counter); }

};

template <typename T>
class SharedPtr {

	typedef T* Ptr;
	Ptr ptr;

public:

	SharedPtr() : ptr(NULL) { }
	SharedPtr(const SharedPtr<T> &rhs) { ptr = rhs.ptr; if (ptr) { ptr->addRef(); } }
	SharedPtr(T * ptr_) { ptr = ptr_; if (ptr) { ptr->addRef(); } }
	~SharedPtr() { if (ptr) ptr->removeRef(); }


	Ptr operator->() { return(ptr); }

	SharedPtr& operator=(T  *ptr_) {

		if (ptr) {
			ptr->removeRef();
		}
		ptr = ptr_;

		if (ptr) {
			ptr->addRef();
		}

		return(*this);

	}

	SharedPtr& operator=(const SharedPtr<T>& rhs) {

		if (ptr) {
			ptr->removeRef();
		}

		ptr = rhs.ptr;

		if (ptr) {
			ptr->addRef();
		}

		return(*this);

	}

	bool operator < (const SharedPtr<T> &rsh) const { return(ptr < rsh.ptr); }

	operator Ptr() const { return(ptr); }
	//const operator Ptr() const { return( ptr ); } 
	//const Ptr operator*() const { return( ptr ); } 

};

void DebugLog(const char* format, ...);

}

#define check(param)  assert(param)