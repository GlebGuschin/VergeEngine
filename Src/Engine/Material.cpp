#include "Material.hpp"
#include "MaterialManager.hpp"

namespace Verge3D {


void MaterialLayer::setTexture(Texture* texture, MaterialTextureType type) {

	textures[type] = texture;
}

Texture* MaterialLayer::getTexture(MaterialTextureType type) const {

	return textures[type];

}



void MaterialAsset::setTexture(Texture* texture, MaterialTextureType type) {

}

Texture* MaterialAsset::getTexture(MaterialTextureType type) {

	Texture* texture = nullptr;

	return texture;

}





Material::~Material() {

	manager->destroyMaterial(this);

}

void Material::setTexture(Texture* texture, MaterialTextureType type, MaterialLayer* layer_) {

	MaterialLayer* layer = layer_ == nullptr ? layers[0].get() : layer_;

	checkLayer(layer); 

	layer->setTexture(texture, type);

	//textures[type] = texture;

}

Texture* Material::getTexture(MaterialTextureType type, MaterialLayer* layer_) {

	MaterialLayer* layer = layer_ == nullptr ? layers[0].get() : layer_;

	checkLayer(layer);

	return layer->getTexture(type);
}

void Material::reloadFromAsset() {

	if (!asset) {
		return;
	}

}

Material* Material::clone() const {

	check(manager);
	return manager->cloneMaterial(this);

}

MaterialLayer* Material::addMaterialLayer(const Name& name) {

	MaterialLayer* materialLayer = new MaterialLayer;
	materialLayer->setName(name);
	layers.add(materialLayer);
	return materialLayer;

}

MaterialLayer* Material::getMaterialLayer(uint32_t index) const {

	return layers[index];

}

MaterialLayer* Material::getMaterialLayer(const Name& name) const {

	for (uint32_t i = 0; i < layers.size(); i++) {
		MaterialLayer* layer = layers[i];
		if (layer->getName() == name) return layer;
	}

	return nullptr;

}

bool Material::checkLayer(MaterialLayer* layer) const {

	for (uint32_t i = 0; i < layers.size(); i++) {		
		if (layers[i] == layer) return true;
	}

	return false;
}

}

/*
	void setBlendType(MaterialBlendType blendType_) {
		blendType = blendType_;
	}

	MaterialBlendType getBlendType() const { return blendType; }
	void setAlphaRef(float alphaRef_) { alphaRef = alphaRef_; }
	float getAlphaRef() const { return alphaRef; }
	void setTransparency(float v) { opacity = v; }
	float getTransparency() const { return opacity; }
	void setTwoSided(bool v) { twoSided = v; }
	bool getTwoSided() const { return twoSided; }

*/
