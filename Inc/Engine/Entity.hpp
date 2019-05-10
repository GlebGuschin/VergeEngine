#pragma once

#include "Component.hpp"

namespace Verge3D {

class EntityListener {

public:

	virtual void onTransformChanged(Entity*) = 0;

};


class Entity : public Referenceable {

	DynamicArray<SharedPtr<Component>> components;
	DynamicArray<SharedPtr<Entity>> entities;
	World* world;
	//void* world;
	Name name;

	Entity* parent;

	Transform transform;
	float lifeTime, lifeTimeLimit;

protected:

	virtual void onEnterWorld();
	virtual void onLeaveWorld();

	void reset();
	
public:

	Entity() { reset(); }

	void setLifeTimeLimit(float v);
	bool isAlive() const;

	void setTransform(const Transform& transform_);

	void setName(const Name& name_) { name = name_; }
	const Name& getName() const { return name; }
	
	void setParent(Entity*);
	Entity* getParent() const;

	World* getWorld() const;
	void setWorld(World*world_);
	
	virtual bool isChild(Entity*) const;
	virtual bool addChild(Entity*);
	virtual bool removeChild(Entity*);
	virtual unsigned getNumChildren(bool recursive=0) const;
	Entity* getChild(unsigned index) const;
	//DynamicArray<Entity*> getChildren() const;


	virtual bool isComponent(Component*) const;
	virtual bool addComponent(Component*);
	virtual bool removeComponent(Component*);
	virtual void removeAllComponents();
	virtual unsigned getNumComponents() const;
	virtual Component* getComponent(unsigned) const;

	template<typename T>
	T* findComponent() const {
		T* ptr = nullptr;
		for (unsigned i = 0; i < components.size(); i++) {
			Component* component = components[i];
			ptr = dynamic_cast<T*>(component);
			if (ptr) break;
		}
		return ptr;
	}

	template<typename T>
	DynamicArray<T*> findComponents() const {
		DynamicArray<T*> array;
		T* ptr = nullptr;
		for (unsigned i = 0; i < components.size(); i++) {
			Component* component = components[i];
			ptr = dynamic_cast<T*>(component);
			if (ptr) {
				array.add(ptr);
			}
		}
		return array;
	}

	void dump(unsigned len=0);
	void update(float deltaTime);

	//bool write(XMLNode*);
	//bool read(XMLNode*);

};

}