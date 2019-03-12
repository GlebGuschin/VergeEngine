#include "CoreModule.hpp"
#include "Framework.hpp"

namespace Verge3D {

/*

class File : public Referenceable {

	public:

bool File::read() {

}

bool File::write();
size_t File::getSize();

	};

	class FileSystemManager : public Referenceable {

		DynamicArray<File*> files;

	public:

		virtual File* createFile(const FileName&);
		virtual void releaseFile(File*);

	};

*/




bool CoreModule::init(Framework* framework_) { 

	Module::init(framework_);
	
	getFramework()->getLogger()->info(L"CoreModule initialized...");
	
	assetManager = new AssetManager(this);

	return true; 

}

void CoreModule::shutdown() {

	delete assetManager;

}

void CoreModule::update(float td) {

}

}