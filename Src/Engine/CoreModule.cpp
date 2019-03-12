#include "CoreModule.hpp"
#include "Framework.hpp"

namespace Verge3D {



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