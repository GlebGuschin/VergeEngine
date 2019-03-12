#include "Asset.hpp"

namespace Verge3D {

class CoreModule;

class AssetManager {

	friend class Asset;

	//typedef std::map<AssetName, SharedPtr<Asset>> Map;
	typedef std::map<AssetName, Asset*> Map;
	Map map;

	CoreModule* coreModule;

public:

	AssetManager(CoreModule* coreModule_) : coreModule(coreModule_) {}

	CoreModule* getCoreModule() const { return coreModule; }

	template<typename T>
	T* createAsset(const AssetName& name) {

		T* ptr = findAsset<T>(name);
		if (ptr) return ptr;

		ptr = new T(name, this);
		map.insert(Map::value_type(name, ptr));

		return ptr;
	}

	void releaseAsset(Asset*) {

	}

	template<typename T>
	T* findAsset(const AssetName& name) {

		Map::iterator it = map.find(name);
		if (it == map.end()) return nullptr;

		T* ptr = dynamic_cast<T*>((Asset*)it->second);

		return ptr;
	}

};


}