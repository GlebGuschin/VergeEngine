#pragma once

#include "Module.hpp"
#include "Logger.hpp"
#include "DynamicArray.hpp"

namespace Verge3D {



class Framework : public Referenceable {

	SharedPtr<Logger> logger;

	DynamicArray<SharedPtr<Module>> modules;

	void addModule(Module*);
	void removeModule(Module*);

public:

	template<typename T>
	T* findModule() {
		T* module = nullptr;
		for (size_t i = 0; i < modules.size(); i++) {
				Module* m = modules[i];
				module = dynamic_cast<T*>(m);
				if (module) {
					return module;
				}
		}
		return nullptr;
	}

	/*
		template<typename T>
		T* installModule(const String&) { return nullptr; }

		template<typename T>
		Module* uninstallModule<T>(const String&) { return nullptr; }
	*/


	virtual bool init();
	virtual void shutdown();
	virtual void tick();

	Logger* getLogger() const { return logger; }

};


}