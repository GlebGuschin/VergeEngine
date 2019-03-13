#pragma once

#include "Material.hpp"

namespace Verge3D {

class MaterialManager : public Referenceable {

	DynamicArray<Material*> materials;

	RenderModule* renderModule;

protected:

	void addMaterial(Material*);
	void removeMaterial(Material*);

public:

	MaterialManager(RenderModule* rm) : renderModule(rm) {}

	virtual Material* createMaterial();
	virtual Material* createMaterial(const AssetName&);

	virtual void destroyMaterial(Material*);

	virtual Material* cloneMaterial(Material*);

};

}