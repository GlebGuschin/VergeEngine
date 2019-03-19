#pragma once

#include "Module.hpp"
#include "MemoryManager.hpp"
#include "FileSystemManager.hpp"
#include "AssetManager.hpp"


namespace Verge3D {

class CoreModule : public Module {

	MemoryManager* memoryManager;
	FileSystemManager* fileSystemManager;
	AssetManager* assetManager;

public:

	CoreModule() : Module("CoreModule"), fileSystemManager(nullptr), assetManager(nullptr) {
			
	}


	bool init(Framework* framework_);

	void shutdown();
	void update(float td);

	MemoryManager* getMemoryManager() const { return memoryManager; }
	FileSystemManager* getFileSystemManager() const { return fileSystemManager; }
	AssetManager* getAssetManager() const { return assetManager; }

};

}