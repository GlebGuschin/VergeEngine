#include "Material.hpp"
#include "MaterialManager.hpp"

namespace Verge3D {



void MaterialAsset::setTexture(Texture* texture, MaterialTextureType type) {

}

Texture* MaterialAsset::getTexture(MaterialTextureType type) {

	Texture* texture = nullptr;

	return texture;

}





Material::~Material() {

	manager->destroyMaterial(this);

}

void Material::setTexture(Texture* texture, MaterialTextureType type) {

	textures[type] = texture;

}

Texture* Material::getTexture(MaterialTextureType type) {

	return textures[type];
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
