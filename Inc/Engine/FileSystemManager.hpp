#include "Common.hpp"
#include "DynamicArray.hpp"
#include "String.hpp"

namespace Verge3D {

//typedef String FileName;
class MemoryBuffer;
class CoreModule;
class FileSystemManager;

enum class FileAccessType {
	Read,
	Write
};

class File : public Referenceable {

	FileSystemManager* manager;
	FileName name;
	bool valid;
	FileAccessType fileAccessType;
	//size_t size;

public:

	File(FileSystemManager* manager_) : manager(manager_), valid(false) {}
	~File();

	virtual bool open(const FileName& name, FileAccessType fileAccessType = FileAccessType::Read);
	virtual void close();
	virtual void flush();

	virtual bool read(size_t size, void* ptr);
	virtual bool write(size_t size, const void* ptr);
	//virtual size_t getSize();
	//virtual void setPos(size_t offset);

};

class FileSystemManager : public Referenceable {

	DynamicArray<File*> files;
	CoreModule* coreModule;

public:

		FileSystemManager(CoreModule* coreModule_) : coreModule(coreModule_) {}

		virtual File* createFile();
		virtual void destroyFile(File*);

		virtual MemoryBuffer* loadFile(const FileName&);

		virtual bool collectFiles(const String& path, const String& ext, DynamicArray<FileName>&, bool recursive = false);

};



}

