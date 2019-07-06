#pragma once

#include "RenderScene.hpp"
#include "Entity.hpp"


namespace Verge3D {

class World;
class Entity;
class Component;


class WorldListener {
public:

	virtual void onSpawnEntity(Entity*) {}
	virtual void onDestroyEntity(Entity*) {}

};

struct EntitySpawnInfo {
	Transform transform;
};

struct EntityDestroyInfo {
	int i;
};


class World : public Referenceable {

protected:

	DynamicArray<WorldListener*> listeners;
	SharedPtr<Entity> rootEntity;
	DynamicArray<Entity*> entities;

	SharedPtr<RenderScene>  renderScene;

	DynamicArray<SharedPtr<Component>> components, tickableComponents;

	float totalTime;
	
	uint32_t entityCounter;

	uint32_t getNewEntityCounter() { return entityCounter++; }

public:

	World() : totalTime(0.0f), entityCounter(1) {
		rootEntity = new Entity;
		rootEntity->setName("Root");
	}

	~World() {
		rootEntity = nullptr;

	}


	Entity* getRoot() const { return rootEntity; }

	/*
	virtual bool spawnEntity(Entity* entity, Entity* parent=nullptr, const EntitySpawnInfo& info = EntitySpawnInfo() ) { 
		return false; 
	};
	virtual bool destroyEntity(Entity* entity, const EntityDestroyInfo& info = ) { return false; }
	*/
		
	virtual bool spawnEntity(const EntitySpawnInfo&);

	virtual bool spawnEntity(Entity* entity, Entity* parent = nullptr);
	virtual bool destroyEntity(Entity* entity);

	virtual void registerComponent(Component*);
	virtual void unregisterComponent(Component*);

	virtual void update(float);
	virtual void dump();

	void addListener(WorldListener* listener);	
	void removeListener(WorldListener* listener);

};

}
