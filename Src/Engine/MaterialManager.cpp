#include "MaterialManager.hpp"

namespace Verge3D {


void MaterialManager::addMaterial(Material* material) {

	materials.add(material);

}

void MaterialManager::removeMaterial(Material* material) {

	materials.remove(material);

}
	
Material* MaterialManager::createMaterial() {

	Material* material = new Material(this);

	addMaterial(material);

	return material;

}

Material* MaterialManager::createMaterial(const AssetName& name) {

	Material* material = nullptr;

	return material;

}

void MaterialManager::destroyMaterial(Material* material) {

	removeMaterial(material);

}

Material* MaterialManager::cloneMaterial(Material* srcMaterial) {

	Material* dstMaterial = nullptr;

	return dstMaterial;

}

}