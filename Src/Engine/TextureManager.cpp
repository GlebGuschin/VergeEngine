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

	renderModule->info(L"Texture created...");

	renderModule->getFramework()->findModule<CoreModule>()->getAssetManager()->createAsset<TextureAsset>(name);


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