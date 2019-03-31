#pragma once

#include "Material.hpp"
#include "TextureManager.hpp"


namespace Verge3D {

class MaterialManager : public Referenceable {

	DynamicArray<Material*> materials;

	RenderModule* renderModule;

	SharedPtr<Material> defaultMaterial;

protected:

	void addMaterial(Material*);
	void removeMaterial(Material*);

public:

	MaterialManager(RenderModule* rm);
	~MaterialManager();

	virtual Material* createMaterial();
	virtual Material* createMaterial(const AssetName&);

	virtual void destroyMaterial(Material*);

	virtual Material* cloneMaterial(Material*);

	Material* getDefaultMaterial() const { return defaultMaterial; }

};

}