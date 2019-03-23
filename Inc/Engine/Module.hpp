#pragma once

#include "Common.hpp"
#include "String.hpp"
#include "DynamicArray.hpp"


namespace Verge3D {

class Framework;

class Module : public Referenceable {

	Framework*  framework;

protected:

	//Framework*  getFramework() const { return framework; }

	String name;

	//virtual void onInit() {}
	//virtual void onShutdown();


public:

	Module(const char* name_) {
		name = String(name_);
	}

	virtual bool init(Framework* framework_) { framework = framework_; return true; }
	
	virtual void shutdown() {}
	virtual void update(float td) {}

	void logInfo(const wchar_t* format, ...);
	void logError(const wchar_t* format, ...);
	void logWarning(const wchar_t* format, ...);

	Framework* getFramework() const { return framework; }

};

}
