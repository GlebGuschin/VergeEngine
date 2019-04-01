#include "MaterialManager.hpp"
#include "RenderModule.hpp"

namespace Verge3D {


MaterialManager::MaterialManager(RenderModule* rm) {
	
	renderModule = rm;

	TextureManager* textureManager = rm->getTextureManager();
	SharedPtr<Texture> texture1 = textureManager->createTexture("Content/Textures/cats.dds");
	SharedPtr<Texture> texture2 = textureManager->createTexture("Content/Textures/cats.dds");
	SharedPtr<Texture> texture3 = textureManager->createTexture("Content/Textures/cookie.dds");
	SharedPtr<Texture> texture4 = textureManager->createTexture("Content/Textures/particle.dds");

	defaultMaterial = createMaterial();

	defaultMaterial->setTexture(texture1, MaterialTextureType::Default);
	defaultMaterial->setTexture(texture3, MaterialTextureType::Detail);
	defaultMaterial->setTexture(texture4, MaterialTextureType::Emission);

}

MaterialManager::~MaterialManager() {

}

void MaterialManager::addMaterial(Material* material) {

	materials.add(material);

}

void MaterialManager::removeMaterial(Material* material) {

	materials.remove(material);

}
	
Material* MaterialManager::createMaterial() {

	Material* material = new Material(this);

	material->addMaterialLayer("DefaultLayer");

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

Material* MaterialManager::cloneMaterial(const Material* srcMaterial) {

	Material* dstMaterial = createMaterial();

	dstMaterial->setInfo(srcMaterial->getInfo());

	for (uint32_t layerIdx = 0; layerIdx < srcMaterial->getNumMaterialLayers(); layerIdx++) {
		for (uint32_t texIdx = 0; texIdx < (uint32_t)MaterialTextureType::Max; texIdx++) {

		}
	}
	 
	return dstMaterial;

}

}