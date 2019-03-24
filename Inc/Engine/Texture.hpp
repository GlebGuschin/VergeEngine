#pragma once

#include "RenderCommon.hpp"
#include "Asset.hpp"


namespace Verge3D {


enum class TexelType : uint32_t {
		Unknown,
		RGBA8,
		R32F,
		R32U,
		DXT1,
		DXT5,
		BC3,
		Max
};

enum class TextureType : uint32_t {
		Tex2D,
		Tex3D,
		TexCube,
		Tex2DArray,
		Max
};

struct TextureInfo {
	TextureType type;
	TexelType texelType;
	uint32_t width, height, depth;
	bool renderTarget;
};

class TextureAsset : public Asset {

protected:

	void onLoad();

public:

	TextureAsset(const AssetName& name, AssetManager* manager) : Asset(name, manager) {}
};


class Texture : public Referenceable {

	TextureInfo info;
	SharedPtr<TextureAsset> asset;
	TextureManager* manager;

public:

	Texture(TextureManager* manager_, const TextureInfo& info_) : manager(manager_), info(info) {}
	Texture(TextureManager* manager_, TextureAsset* asset_) : manager(manager_), asset(asset_) {}

	TextureAsset* getAsset() const { return asset; }
	const TextureInfo& getInfo() const { return info; }

};

}
