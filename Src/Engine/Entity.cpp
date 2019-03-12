#include "Entity.hpp"
#include "World.hpp"

namespace Verge3D {

void Entity::setParent(Entity* parent_) {

	parent = parent_;

}

Entity* Entity::getParent() const {

	return parent;
}

World* Entity::getWorld() const {

	return world;

}

void Entity::setWorld(World*world_) {

	if (world || world_ == nullptr) {
			onLeaveWorld();
	}

	world = world_;
	onEnterWorld();

}

bool Entity::isChild(Entity* entity) const {

	return entities.find(entity);

}

bool Entity::addChild(Entity*entity) {

	entities.add(entity);

	entity->setParent(this);

	return true;

}

bool Entity::removeChild(Entity*entity) {

	entity->setParent(nullptr);

	entities.remove(entity);

	return true;

}

bool Entity::isComponent(Component*component) const {
	return components.find(component);
}

bool Entity::addComponent(Component*component) {
	components.add(component);
	return true;
}

bool Entity::removeComponent(Component*component) {
	components.remove(component);
	return true;
}

void Entity::removeAllComponents() {
	components.clear();
}

unsigned Entity::getNumComponents() const { 
	return components.size(); 
}
Component* Entity::getComponent(unsigned index) const { return components[index]; }

void Entity::onEnterWorld() {

	DebugLog("Entity::onEnterWorld()");

	assert(world);

	for (size_t i = 0; i < components.size(); i++) {
		//world->registerComponent(components[i]);
	}
}

void Entity::onLeaveWorld() {

	for (size_t i = 0; i < components.size(); i++) {
		//world->unregisterComponent(components[i]);
	}

	DebugLog("Entity::onLeaveWorld()");
}

unsigned Entity::getNumChildren(bool recursive) const {
	unsigned num = 0;	
	if (recursive) {
		for (size_t i = 0; i < entities.size(); i++) {
			Entity* e = entities[i];
			num += e->getNumChildren(true);			
		}
	}
	num += entities.size();	
	return num;
}

Entity* Entity::getChild(unsigned index) const {
	return entities[index];
}


void Entity::dump(unsigned len) {

	std::string string;
	for (unsigned i = 0; i < len; i++) string += ' ';
	string += "Name: %s";
	DebugLog(string.c_str(), (const char*)name);
	len += 3;
	for (unsigned i = 0; i < entities.size(); i++)entities[i]->dump(len);
	//Logw(pattern, 10);
}


/*
bool Entity::write(XMLNode* node) {


	//for (unsigned i = 0; i < entities.size(); i++)entities[i]->dump();

	return true;
}

bool Entity::read(XMLNode* node) {
	return true;
}
*/


/*
DynamicArray<Entity*> Entity::getChildren() const {
	return 
}
*/

}