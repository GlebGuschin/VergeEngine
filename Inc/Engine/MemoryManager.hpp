#pragma once

#include "DynamicArray.hpp"


namespace Verge3D {

class MemoryManager;
class CoreModule;

struct MemoryBufferInfo {
	size_t size;
	unsigned flags;
};



class MemoryBuffer : public Referenceable {
//class MemoryBuffer {

	size_t size;
	void* ptr;
	MemoryManager* manager;

protected:

	unsigned lockCounter; // atomic ?

public:

	MemoryBuffer() : size(0), lockCounter(0), ptr(nullptr) {}

	MemoryBuffer(MemoryManager* manager_, void* ptr_, size_t size_, unsigned flags=0) : 
		manager(manager_),
		size(size_), 
		ptr(ptr_), 
		lockCounter(0) {
	
	}

	MemoryBuffer(void* ptr_, size_t size_) : size(size_), ptr(ptr_), lockCounter(0) {}
	~MemoryBuffer();


	size_t getSize() const { return size; }
	void* getPtr() const { return ptr; }

	virtual void* lock(unsigned flags = 0) {
		lockCounter++;
		return ptr;
	}

	virtual void  unlock() {
		lockCounter--;
	}

};



class MemoryManager {

	DynamicArray<MemoryBuffer*> buffers;
	CoreModule* coreModule;

public:

	MemoryManager(CoreModule* coreModule_) : coreModule(coreModule_) {}

	MemoryBuffer* createMemoryBuffer(size_t size, unsigned flags = 0); 
	//MemoryBuffer* createMemoryBuffer(MemoryBuffer* parentBuffer, size_t size, size_t offset, unsigned flags = 0);
	void destroyMemoryBuffer(MemoryBuffer*);

};


};