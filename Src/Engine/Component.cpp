
#include "Component.hpp"

namespace Verge3D {

void Component::onStart() {

}

void Component::onStop() {

}

void Component::setWorld(World*world_) { 
	world = world_; 
}

void Component::onUpdate(float timeDelta) {

	DebugLog("Component::onUpdate");

}

/**
bool Component::write(XMLNode* node) {

	//for (unsigned i = 0; i < entities.size(); i++)entities[i]->dump();

	return true;
}

bool Component::read(XMLNode* node) {
	return true;
}


Component* CreateComponent(const char* name) {

	if (strcmp(name, "ZoneComponent")) return CreateComponent<ZoneComponent>();

	return nullptr;
}
*/

}

