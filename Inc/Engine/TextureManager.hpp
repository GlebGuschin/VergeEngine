#pragma once

#include "Texture.hpp"


namespace Verge3D {

class RenderModule;

class TextureManager : public Referenceable {

		DynamicArray<Texture*> textures;
		RenderModule* renderModule;

protected:

		void addTexture(Texture*);
		void removeTexture(Texture*);

public:

	TextureManager(RenderModule* renderModule_) : renderModule(renderModule_) {}

	virtual Texture* createTexture(const AssetName&);
	virtual Texture* createTexture(const TextureInfo&);
	virtual void destroyTexture(Texture*);

};


}