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

public:

	Module(const char* name_) {
		name = String(name_);
	}

	virtual bool init(Framework* framework_) { framework = framework_; return true; }
	
	virtual void shutdown() {}
	virtual void update(float td) {}

	void info(const wchar_t* format, ...);
	void error(const wchar_t* format, ...);
	void warning(const wchar_t* format, ...);

	Framework* getFramework() const { return framework; }

};

}
