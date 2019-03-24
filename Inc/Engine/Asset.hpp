#pragma once
#include "Common.hpp"
#include "String.hpp"
#include "Name.hpp"
#include "MemoryManager.hpp"


namespace Verge3D {

typedef String AssetName;


enum AssetState {
	Empty,
	Loading,
	Storing
	//ASSET_STATE_LOADED,
	//ASSET_STATE_UNLOADING
};

class MemoryBuffer;
class MemoryManager;
class Asset;
class AssetManager;

struct AssetUpdateInfo {
	Name aspectName;
};

class AssetListener {
public:

	virtual void onStartLoading(Asset*) {}
	virtual void onFinishLoading(Asset*) {}
	virtual void onUpdate(Asset*, const AssetUpdateInfo&) {}
};

class Asset : public Referenceable {

	AssetManager* assetManager;
	AssetState state;
	DynamicArray<AssetListener*>  listeners;
	bool dirty;

protected:

	SharedPtr<MemoryBuffer> defaultMemoryBuffer;
		//MemoryBuffer* defaultMemoryBuffer;

	virtual void onLoad() {}
	virtual void onUnload() {}

	virtual void onReload() {}

	bool loadFromFile();
	bool saveToFile();

	AssetName name;

public:

	//Asset() : state(ASSET_STATE_EMPTY) {}
	Asset(const AssetName& name_, AssetManager* assetManager_ = nullptr) :
			state(AssetState::Empty),
			name(name_),
			dirty(false),
			assetManager(assetManager_) {}

	void addListener(AssetListener*listener);
	void removeListener(AssetListener*listener);

	bool isDirty() const { return dirty; }

	AssetState getState() const { return state; }

	virtual void load();
	virtual void unload() {}
	virtual void reload() {}
	virtual void save() {}

	//void setManager(AssetManager* assetManager_) { assetManager = assetManager_; }
	//AssetManager* getManager() const { return assetManager; }

};



}
