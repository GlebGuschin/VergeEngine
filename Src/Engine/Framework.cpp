
#include "Framework.hpp"
#include "CoreModule.hpp"
#include "InputModule.hpp"
#include "RenderModule.hpp"

using namespace Verge3D;


bool Framework::init() {

	logger = new Logger;
	logger->open("Verge3D.log");

	/*
	logger->log(LogType::Error, L"Wrong file");
	logger->log(LogType::Info, L"Process started");
	logger->log(LogType::Warning, L"1");
	*/


	addModule(new CoreModule);
	addModule(new InputModule);
	addModule(CreateRenderModule());

	return true;
}

void Framework::shutdown() {

	for (uint32_t i = 0; i < modules.size(); i++) {
		modules[i]->shutdown();
	}

	logger->close();

}

void Framework::tick() {

	for (uint32_t i = 0; i < modules.size(); i++) {
		modules[i]->update(0.1f);
	}

}

void Framework::addModule(Module* module) {

	bool ok = module->init(this);

	modules.add(module);
}

void Framework::removeModule(Module* module) {

	modules.remove(module);

}

