#include "CoreModule.hpp"
#include "Framework.hpp"

namespace Verge3D {



bool CoreModule::init(Framework* framework_) { 

	Module::init(framework_);
	
	info(L"CoreModule initialized...");
	
	memoryManager = new MemoryManager(this);
	fileSystemManager = new FileSystemManager(this);
	assetManager = new AssetManager(this);

	return true; 

}

void CoreModule::shutdown() {

	delete assetManager;
	delete fileSystemManager;
	delete memoryManager;

	info(L"CoreModule shutdowned...");

}

void CoreModule::update(float td) {

}

}