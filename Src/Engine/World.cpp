#include "World.hpp"

namespace Verge3D {


void World::registerComponent(Component* component) {

	components.add(component);

	if (component->isTickable()) {
		tickableComponents.add(component);
	}

	component->setWorld(this);

}

void World::unregisterComponent(Component* component) {

	if (component->isTickable()) {
		tickableComponents.remove(component);
	}

	components.remove(component);

	component->setWorld(nullptr);

}

void World::update(float deltaTime) {

	totalTime += deltaTime;

	for (size_t i = 0; i < components.size(); i++) {
		components[i]->onUpdate(deltaTime);
	}



}

void World::dump() {

	DebugLog(" ");
	DebugLog("World dump...");
	DebugLog("    Time passed: %f", totalTime);
	DebugLog("	 Num entities: %u", getRoot()->getNumChildren(true)+1);

	getRoot()->dump();

}

bool World::spawnEntity(const EntitySpawnInfo& info) {

	return true;

}

bool World::spawnEntity(Entity* entity, Entity* parent) {

	if (parent == nullptr) {
		parent = getRoot();
	}

	char buffer[128];
	sprintf_s(buffer,"Entity%u", getNewEntityCounter() );
	entity->setName(Name(buffer));

	parent->addChild(entity);

	entity->setWorld(this);
	

	for (size_t i = 0; i < listeners.size(); i++) {
		listeners[i]->onSpawnEntity(entity);
	}

	entities.add(entity);

	DebugLog("Entity spawned");
	
	return true;
}

bool World::destroyEntity(Entity* entity) {

	entities.remove(entity);

	check(entity);
	check(entity->getWorld() == this);
	Entity* parent = entity->getParent();
	check(parent);

	

	for (size_t i = 0; i < listeners.size(); i++) {
		listeners[i]->onDestroyEntity(entity);
	}

	parent->removeChild(entity);

	DebugLog("Entity destroyed");
	return true;
}

void World::addListener(WorldListener* listener) {

	listeners.add(listener);

}

void World::removeListener(WorldListener* listener) {

	listeners.remove(listener);

}


}

