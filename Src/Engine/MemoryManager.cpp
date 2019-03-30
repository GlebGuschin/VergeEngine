#include "MemoryManager.hpp"

namespace Verge3D {

MemoryBuffer::~MemoryBuffer() {

	check(manager);
	manager->destroyBuffer(this);

}

MemoryBuffer* MemoryManager::createBuffer(size_t size, unsigned flags) {

	void* ptr = malloc(size);
	MemoryBuffer* buffer = nullptr;
	buffer = new MemoryBuffer(this, ptr, size, flags);

	buffers.add(buffer);

	return buffer;

}
	//MemoryBuffer* createBuffer(MemoryBuffer* parentBuffer, size_t size, size_t offset, unsigned flags = 0);
MemoryBuffer* MemoryManager::createBuffer(File* file) {

	MemoryBuffer* buffer = nullptr;

	return buffer;

}

void MemoryManager::destroyBuffer(MemoryBuffer* buffer) {

	buffers.remove(buffer);

	free(buffer->getPtr());

	int i = 0;
}


};