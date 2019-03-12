#include "Common.hpp"
#include "DynamicArray.hpp"
#include "String.hpp"

namespace Verge3D {

//typedef String FileName;

class File : public Referenceable {

public:

	virtual bool read(size_t size, void* ptr);
	virtual bool write(size_t size, const void* ptr);
	virtual size_t getSize();
	virtual void setPos(size_t offset);

};

class FileSystemManager : public Referenceable {

	DynamicArray<File*> files;

public:

		virtual File* createFile(const FileName&);
		virtual void destroyFile(File*);

};



}

