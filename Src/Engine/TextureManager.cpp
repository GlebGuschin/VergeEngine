#include "TextureManager.hpp"
#include "RenderModule.hpp"
#include "CoreModule.hpp"
#include "Framework.hpp"



namespace Verge3D {

void TextureManager::addTexture(Texture* texture) {

	textures.add(texture);
}

void TextureManager::removeTexture(Texture* texture) {

	textures.remove(texture);

}

Texture* TextureManager::createTexture(const AssetName& name) {

	Texture* texture = nullptr;
	
	SharedPtr<TextureAsset> textureAsset = renderModule->getFramework()->findModule<CoreModule>()->getAssetManager()->createAsset<TextureAsset>(name);

	textureAsset->load();

	renderModule->info(L"Texture created...");	

	for (uint32_t i = 0; i < textures.size(); i++) {
		if (textures[i]->getAsset() == textureAsset) {
			return textures[i];
		}
	}

	texture = new Texture(this, textureAsset);
	addTexture(texture);

	return texture;

}

Texture* TextureManager::createTexture(const TextureInfo& info) {

	Texture* texture = nullptr;

	texture = new Texture(this, info);
	addTexture(texture);

	return texture;

}

void TextureManager::destroyTexture(Texture*) {

}

}