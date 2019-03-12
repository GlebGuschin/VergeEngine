#pragma once

#include "RenderCommon.hpp"
#include "ParticleSystem.hpp"


namespace Verge3D {

class RenderSceneObject;


class RenderSceneObjectListener {
public:
		virtual void onChangeTransform(RenderSceneObject*) {}
};



class RenderSceneObject : public Referenceable {

	DynamicArray<RenderSceneObjectListener*> listeners;

	Transform transform;

	//AABB aabb;
	float totalTime;
	RenderScene* renderScene;

public:

	RenderSceneObject(RenderScene* renderScene_) : renderScene(renderScene_) {}

	RenderScene* getScene() const { return renderScene; }

	//const AABB& getAABB() { return aabb; }

	void addListener(RenderSceneObjectListener*listener);
	void removeListener(RenderSceneObjectListener*listener);

	virtual void setTransform(const Transform&);

	//virtual void setPosition(const Vector3&) {}
	//virtual void setRotation(const Quaternion&) {}

	//virtual void update(float deltaTime) {}
};


/*
struct FogInfo {
		Color startColor, endColor;
};
*/


enum LightType {
	Directional,
	Omni,
	Spot
};

struct LightInfo {
	LightType type;
	float radius;
	float coneAngle;
	LightInfo() : type(LightType::Directional) {}
};


class LightRenderSceneObject : public RenderSceneObject {

	LightInfo info;
	//Color color;

public:

	LightRenderSceneObject(RenderScene* renderScene_) : RenderSceneObject(renderScene_) {}
	~LightRenderSceneObject() {}

	void setType(LightType type_) { info.type = type_; }
	LightType getType() const { return info.type; }
	//void setColor(const Color&) {}
	//LightRenderSceneObject(const LightInfo& info_) : info(info_) {}
	//void setType

};


class ParticleSystemRenderSceneObject : public RenderSceneObject {
	
	SharedPtr<ParticleSystem> particleSystem;

	//ParticleStorage particleStorage;

public:

	ParticleSystemRenderSceneObject(RenderScene* renderScene_) : RenderSceneObject(renderScene_) {}
	~ParticleSystemRenderSceneObject() {}

	//virtual ParticleSystem* getParticleSystem() const { return particleSystem; }
	//virtual void setParticleSystem(ParticleSystem*particleSystem_) {}
};


enum DebugRenderType {
	None,
	Line, 
	WiredCube,
	SolidCube,
	WiredSphere,
	SolidSphere
};

struct DebugRenderItem {
	DebugRenderType type;
	union {
		struct {
			Vector startLine, endLine;
		};
		struct {
			Vector cubeSize;
		};
		struct {
			float sphereRadius;
		};
	};
	DebugRenderItem() : type(DebugRenderType::None) {}
	//bool operator==(const DebugRenderItem&) const { return false;  }
};

class DebugRenderSceneObject : public RenderSceneObject {

	std::vector<DebugRenderItem> items;

public:

	DebugRenderSceneObject(RenderScene* renderScene_) : RenderSceneObject(renderScene_) {}
	~DebugRenderSceneObject() {}

	uint32_t getNumItems() const { return (uint32_t)items.size(); }
	const DebugRenderItem& getItem(uint32_t index) const { return items[index]; }
	
	void clear() { items.clear(); }

	void addLine(const Vector& v0, const Vector& v1, const Color& c);
	void addWiredCube(const Vector& origin, const Vector& size, const Color& c);
	void addSolidCube(const Vector& origin, const Vector& size, const Color& c);
	void addWireSphere(const Vector& origin, const float radius, const Color& c);
	void addSolidSphere(const Vector& origin, const float radius, const Color& c);

};



enum RenderSceneObjectType {
		RENDER_SCENE_OBJECT_LIGHT = 0,
		RENDER_SCENE_OBJECT_PS,
		RENDER_SCENE_OBJECT_OCLLUSION_AREA,
		RENDER_SCENE_OBJECT_MAX
};




class RenderScene : public Referenceable, public RenderSceneObjectListener {

	//RenderSystem* renderSystem;
	DynamicArray<RenderSceneObject*> objects;

		/*
		DynamicArray<LightRenderSceneObject*> lights;
		DynamicArray<ParticleSystemRenderSceneObject*> particleSystems;
		DynamicArray<VolumeRenderSceneObject*> volumes;
		DynamicArray<ModelRenderSceneObject*> models;
		*/

		//AABB aabb;

protected:

	void addObject(RenderSceneObject* object);
	void removeObject(RenderSceneObject* object);

public:

		//RenderScene(RenderSystem* renderSystem_) : renderSystem(renderSystem_) {}
	RenderScene() {}

	//const AABB& getAABB() { return aabb; }

	//virtual void destroyLight(LightRenderSceneObject* light);
	//virtual LightRenderSceneObject* createLight();

	
	virtual ParticleSystemRenderSceneObject* createParticleSystem();
	virtual void destroyParticleSystem(ParticleSystemRenderSceneObject*);
	

	virtual DebugRenderSceneObject* createDebug();
	virtual void destroyDebug(DebugRenderSceneObject*);


		//virtual LightRenderSceneObject* createLight(const LightInfo&);
		//virtual ModelRenderSceneObject* createModel();
		
		//virtual ParticleSystemRenderSceneObject* createParticleSystem();
		//virtual OcclusionAreaRenderSceneObject* createOcclusionArea();
		//virtual VolumeRenderSceneObject* createVolume();

		//virtual void destroyModel(ModelRenderSceneObject* model);
		
		//virtual void destroyOcclusionArea(OcclusionAreaRenderSceneObject* area);
		//virtual void destroyParticleSystem(ParticleSystemRenderSceneObject*);
		//virtual void destroyVolume(VolumeRenderSceneObject* volume);

		const DynamicArray<RenderSceneObject*>& getObjects() const { return objects; };
		/*
		const DynamicArray<LightRenderSceneObject*>& getLights() const { return lights; };
		const DynamicArray<ParticleSystemRenderSceneObject*>& getParticleSystems() const { return particleSystems; };
		const DynamicArray<ModelRenderSceneObject*>& getModels() const { return models; };
		*/

		virtual void update(float deltaTime);


		// listener
		virtual void onChangeTransform(RenderSceneObject*);
		

		/*
		virtual ModelRenderSceneObject* createModel();
		virtual void destroyModel(ModelRenderSceneObject*);
		const DynamicArray<SharedPtr<ModelRenderSceneObject>>& getModels() const { return models; }
		virtual DebugRenderSceneObject* createDebug();
		virtual void destroyDebug(DebugRenderSceneObject*);
		*/

};


}

