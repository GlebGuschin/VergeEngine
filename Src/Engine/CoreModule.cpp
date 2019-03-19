#include "CoreModule.hpp"
#include "Framework.hpp"

namespace Verge3D {



bool CoreModule::init(Framework* framework_) { 

	Module::init(framework_);
	
	info(L"CoreModule initialized...");
	
	memoryManager = new MemoryManager(this);
	assetManager = new AssetManager(this);

	return true; 

}

void CoreModule::shutdown() {

	delete assetManager;
	delete memoryManager;

}

void CoreModule::update(float td) {

}

}