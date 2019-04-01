#pragma once

#include "RenderCommon.hpp"
#include "Texture.hpp"
#include "Name.hpp"
#include "Color.hpp"
#include "Asset.hpp"


namespace Verge3D {

class MaterialManager;

enum class CustomRenderParamType : uint32_t {
	Color,
	Bool,
	Float,
	Float3
};

struct CustomRenderParam {
	CustomRenderParamType type;
	Name name;
	union {
		struct {
			Color colorParam;
		};
		struct {
			bool boolParam;
		};

		struct {
			float floatParam;
		};
		struct {
			Vector float3Param;
		};

	};
	CustomRenderParam() {}
	CustomRenderParam(const Name& name_, const Color& value) : type(CustomRenderParamType::Color), name(name_), colorParam(value) { }
	CustomRenderParam(const Name& name_, const Vector& value) : type(CustomRenderParamType::Float3),  name(name_), float3Param(value) { }
	CustomRenderParam(const Name& name_, const bool value) : type(CustomRenderParamType::Bool), name(name_), boolParam(value) { }
	CustomRenderParam(const Name& name_, const float value) : type(CustomRenderParamType::Float), name(name_), floatParam(value) { }
};


class CustomRenderParams {

	std::vector<CustomRenderParam> params;

public:

	void setParam(const Name name, const Color& colorParam_) {
		CustomRenderParam param(name, colorParam_);
		params.push_back(param);
	}

	void setParam(const Name name, const float floatParam_) {
		CustomRenderParam param(name, floatParam_);
		params.push_back(param);
	}

	void setParam(const Name name, const Vector& float3Param_) {
		CustomRenderParam param(name, float3Param_);
		params.push_back(param);
	}

	void setParam(const Name name, const bool boolParam_) {
		CustomRenderParam param(name, boolParam_);
		params.push_back(param);
	}

	void clear() { params.clear(); }

	size_t getNumParams() const { return params.size(); }

	const CustomRenderParam& getParam(uint32_t index) const { return params[index]; }
	//CustomRenderParam& getParam(uint32_t index) const { return params[index]; }

};


struct MaterialCustomParam {
	int i;
};

//MaterialCustomParam

enum class MaterialLightingType : uint8_t {
	Unlit,
	Default
};


enum class MaterialBlendType : uint8_t {
	Opaque,
	Masked,
	Translucent,
	Max
};


struct MaterialTextureParams {
	TextureClampType clampType;
};

enum class MaterialTextureType {
	Default = 0,
	Diffuse = Default,
	Normal,
	Emission,
	AO,
	Metalness,
	Roughness,
	Detail,
	Max
};


class MaterialLayer : public Referenceable {

	Name name;
	SharedPtr<Texture> textures[16];
	Material* material;

public:

	MaterialLayer(Material* material_ = nullptr ) : material(material_) {}

	const Name& getName() const { return name; }
	void setName(const Name& name_) { name = name_; }

	void setTexture(Texture* texture, MaterialTextureType type);
	Texture* getTexture(MaterialTextureType type) const;

};

struct MaterialInfo {
	bool twoSided;
	float alphaRef;
	float opacity;
	MaterialBlendType blendType;
	MaterialInfo() : alphaRef(1.0f), twoSided(true), blendType(MaterialBlendType::Opaque) {}
};

class MaterialParams {

	MaterialInfo info;

protected:

	virtual void onUpdateMaterialParams() {}

public:

	MaterialParams() {}
	//Color diffuseColor, ambientColor;	

	const MaterialInfo& getInfo() const { return info; }
	void setInfo(const MaterialInfo& info_) { info = info_; }	

	void setBlendType(MaterialBlendType blendType_) {
		info.blendType = blendType_;
		onUpdateMaterialParams();
	}

	MaterialBlendType getBlendType() const { return info.blendType; }

	void setAlphaRef(float alphaRef_) { 
		info.alphaRef = alphaRef_;
		onUpdateMaterialParams();
	}

	float getAlphaRef() const { return info.alphaRef; }

	void setTransparency(float v) { 
		info.opacity = v;
		onUpdateMaterialParams();
	}

	float getTransparency() const { return info.opacity; }

	void setTwoSided(bool v) { 
		info.twoSided = v;
		onUpdateMaterialParams();
	}

	bool getTwoSided() const { return info.twoSided; }
	
};




class MaterialAsset : public Asset, public MaterialParams {

public:

	void setTexture(TextureAsset* texture, MaterialTextureType type);

	void setTexture(Texture* texture, MaterialTextureType type);
	Texture* getTexture(MaterialTextureType type);

	//const AssetName& getTexture(MaterialTextureType type);
	//void setTexture(const AssetName&, MaterialTextureType type);

};




class Material : public Referenceable, public MaterialParams, public AssetListener {

	SharedPtr<MaterialAsset> asset;
	DynamicArray<SharedPtr<MaterialLayer>> layers;
	//SharedPtr<Texture> textures[16];
	MaterialManager* manager;

	CustomRenderParams customRenderParams;

public:

	Material(MaterialManager* manager_) : manager(manager_) {}
	~Material();

	//Material() : alphaValue(1.0f), masked(false), blendType(MATERIAL_BLEND_NONE) {}
	//Color diffuseColor, ambientColor;
	//MaterialTextures textures;

	MaterialAsset* getAsset() const { return asset; }


	MaterialLayer* addMaterialLayer(const Name&);
	uint32_t getNumMaterialLayers() const { return layers.size();  }
	MaterialLayer* getMaterialLayer(uint32_t) const;
	MaterialLayer* getMaterialLayer(const Name&) const;
	bool checkLayer(MaterialLayer*) const;

	void setTexture(Texture* texture, MaterialTextureType type, MaterialLayer* layer=nullptr);
	Texture* getTexture(MaterialTextureType type, MaterialLayer* layer = nullptr);

	void reloadFromAsset();

	void setCustomParam(const Name& name, const MaterialCustomParam&) {}
	bool getCustomParam(const Name& name, MaterialCustomParam&) const {}
	size_t getNumCustomParams() const {}

	Material* clone() const;

};


}