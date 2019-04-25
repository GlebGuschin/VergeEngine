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
#include "Math.hpp"


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

}