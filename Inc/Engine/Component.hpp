#pragma once

#include "Common.hpp"

/*
#include "Common/Color.hpp"
#include "Common/Transform.hpp"
#include "Core/MaterialManager.hpp"
#include "Common/XML.hpp"
#include "Audio/Sound.hpp"
#include "Render/ParticleSystem.hpp"
#include "Render/Model.hpp"
*/

#include "DynamicArray.hpp"
#include "Name.hpp"


namespace Verge3D {

class Component : public Referenceable {

protected:
	
	unsigned priority;
	bool unique, tickable;

	
	Entity* entity;
	World* world;

	virtual void onStart();
	virtual void onStop();

public:

	Component() : priority(0), unique(false), tickable(false), entity(nullptr), world(nullptr) {}

	unsigned getPriority() const { return priority; }
	bool isUnique() const { return unique; }
	bool isTickable() const { return tickable; }

	World* getWorld() const { return world; }
	void setWorld(World*);

	Entity* getEntity() const { return entity; }
	void setEntity(Entity*entity_){ entity = entity_; }

	virtual void onUpdate(float timeDelta);

	//virtual bool write(XMLNode*);
	//virtual bool read(XMLNode*);

};



class TransformComponent : public Component {

public:

};

template<typename T> T* CreateComponent() { return new T; }
Component* CreateComponent(const char*);

/*

class ZoneComponent : public Component {

public:

	ZoneComponent() {
		tickable = true;
	}

};

enum PROJECTION_TYPE {
	PROJECTION_PERSPECTIVE,
	PROJECTION_ORTHO
};

struct CameraParams
{
	float zNear, zFar;
	CameraParams() : zNear(0.25f), zFar(10000.0f) {}
};

class CameraComponent : public Component {

public:

};

class TestComponent : public Component {

public:

};



class Model : public Referenced {

	virtual Material* getMaterial(unsigned meshIndex) const { return nullptr; }
	virtual void setMaterial(Material*, unsigned meshIndex) {}

};


class ModelComponent : public Component {

public:

	virtual Material* getMaterial(unsigned meshIndex) const { return nullptr; }
	virtual void setMaterial(Material*, unsigned meshIndex) {}

};


class StaticModelComponent : public ModelComponent {
public:
	//virtual Material* getMaterial(unsigned meshIndex) const { return nullptr; }
	//virtual void setMaterial(Material*, unsigned meshIndex) {}
};

class SkinnedModelComponent : public ModelComponent {
public:
	//virtual Material* getMaterial(unsigned meshIndex) const { return nullptr; }
	//virtual void setMaterial(Material*, unsigned meshIndex) {}
};

class SoundComponent : public Component {
public:
	virtual void setSound(Sound*) {}
};

*/


}