#include "MemoryManager.hpp"

namespace Verge3D {

MemoryBuffer::~MemoryBuffer() {

	check(manager);
	manager->destroyMemoryBuffer(this);

}

MemoryBuffer* MemoryManager::createMemoryBuffer(size_t size, unsigned flags) {

	void* ptr = malloc(size);
	MemoryBuffer* buffer = nullptr;
	buffer = new MemoryBuffer(this, ptr, size, flags);

	buffers.add(buffer);

	return buffer;

}
	//MemoryBuffer* createMemoryBuffer(MemoryBuffer* parentBuffer, size_t size, size_t offset, unsigned flags = 0);

void MemoryManager::destroyMemoryBuffer(MemoryBuffer* buffer) {

	buffers.remove(buffer);

	free(buffer->getPtr());

	int i = 0;
}


};