
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


class TransformComponent : public Component {

public:

};

template<typename T> T* CreateComponent() { return new T; }
Component* CreateComponent(const char*);



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

