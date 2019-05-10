#include "World.hpp"
#include "Common.hpp"
#include "DynamicArray.hpp"
#include "Math.hpp"
#include "Color.hpp"
#include "Name.hpp"
#include "ParticleSystemComponent.hpp"
#include "LightComponent.hpp"
#include "CameraComponent.hpp"
#include "Framework.hpp"
#include "CoreModule.hpp"
#include "RenderModule.hpp"
#include "XML.hpp"

namespace Verge3D {

	class ModelComponent : public Component {
	public:
		virtual Material* getMaterial(unsigned meshIndex) const { return nullptr; }
		virtual void setMaterial(Material*, unsigned meshIndex) {}
	};

	class StaticModelComponent : public ModelComponent {
	public:
		//virtual Material* getMaterial(unsigned meshIndex) const { return nullptr; }
		//virtual void setMaterial(Material*, unsigned meshIndex) {}
	};

	class SkinnedModelComponent : public ModelComponent {
	public:
		//virtual Material* getMaterial(unsigned meshIndex) const { return nullptr; }
		//virtual void setMaterial(Material*, unsigned meshIndex) {}
	};



	
class TimeInfo {

	float deltaTime, totalTime;

public:

	TimeInfo() : deltaTime(0.0f), totalTime(0.0f) {}

	float getTotalTime() const { return totalTime; }
	float getDeltaTime() const { return deltaTime; }

	void tick(float deltaTime_) {
		deltaTime = deltaTime_;
		totalTime += deltaTime;
	}

};



void WorldTest() {

	
	SharedPtr<World> world = new World;

	
	Entity* entity1 = new Entity;
	Entity* entity11 = new Entity;
	Entity* entity111 = new Entity;
	Entity* entity2 = new Entity;

	entity111->addComponent(new ParticleSystemComponent);
	entity111->addComponent(new OmniLightComponent);
	entity111->addComponent(new SpotLightComponent);
	entity111->addComponent(new SkinnedModelComponent);
	entity1->addComponent(new CameraComponent);

	
	

	world->spawnEntity(entity1);
	world->spawnEntity(entity11, entity1);
	world->spawnEntity(entity111, entity11);
	world->spawnEntity(entity2);

	world->dump();

	// particles spawn test
	for (int i = 0; i < 100; i++) {

		Entity* entity = new Entity;
		entity->setLifeTimeLimit(Random<float>(0.1f,1.1f));
		entity->addComponent(new ParticleSystemComponent);
		world->spawnEntity(entity);

	}

	
	world->dump();

	world->destroyEntity(entity1);

	world->update(0.5f);

	world->dump();

	int i = 0;

}

/*
	DynamicArray<int> array;
	String string1("String");
	String string2(L"String");

	Logger* logger = new Logger;
	logger->open("log.txt");

	logger->log(LogType::Error, L"Wrong file");
	logger->log(LogType::Info, L"Process started");
	logger->log(LogType::Warning, L"1");
	
TVector3<float> a1, b1, c1;
a1 = b1 + c1;
//a1 = Calc(b1, c1);
//a2 = Calc(b2, c2);
//a3 += c3;


CustomRenderParams customRenderParams;
customRenderParams.setParam("Color1", Color());
customRenderParams.setParam("Color2", Color());
customRenderParams.setParam("Position", Vector());
customRenderParams.setParam("Check", true);
customRenderParams.setParam("Alpha", 0.5f);
customRenderParams.setParam("SSSScale", 0.5f);

CustomRenderParams customRenderParams2 = customRenderParams;


for (uint32_t i = 0; i < customRenderParams.getNumParams(); i++) {
	const char * name = customRenderParams.getParam(i).name;
	DebugLog("Name = %s", name);
}

Color color1, color2;
Color color3 = Lerp(color1, color2, 0.5f);

SharedPtr<MaterialManager> materialManager = new MaterialManager;

SharedPtr<Material> material = materialManager->createMaterial();

SharedPtr<TextureManager> textureManager = new TextureManager(nullptr);

TextureInfo ti;
SharedPtr<Texture> texture = textureManager->createTexture(ti);

//material->setTexture(new Texture, MaterialTextureType::Default);

/*
SharedPtr<RenderScene> renderScene = new RenderScene;
ParticleSystemRenderSceneObject* psrso = renderScene->createParticleSystem();
DebugRenderSceneObject* drso = renderScene->createDebug();
drso->addLine(Vector(0, 0, 0), Vector(1, 1, 1), Color());
drso->addWiredCube(Vector(0, 0, 0), Vector(1, 1, 1), Color());


renderScene->destroyDebug(drso);
renderScene->destroyParticleSystem(psrso);


Name name1("Verge3D");

SharedPtr<ParticleSystemStream> particleSystemStream = new ParticleSystemStream;

//particleSystemStream->addModule(new SpawnParticleSystemStreamModule);


particleSystemStream->addModule(new InitialSizeParticleSystemStreamModule);
particleSystemStream->addModule(new InitialColorParticleSystemStreamModule);
particleSystemStream->addModule(new InitialLifeTimeParticleSystemStreamModule);
particleSystemStream->addModule(new InitialVelocityParticleSystemStreamModule);

particleSystemStream->addModule(new LifeSizeParticleSystemStreamModule);
particleSystemStream->addModule(new LifeColorParticleSystemStreamModule);



for (int i = 0; i < 100; i++) {
	particleSystemStream->update(0.1f);
}

*/

void ParticleSystemTest() {

	SharedPtr<ParticleSystemStream> particleSystemStream = new ParticleSystemStream;

	//particleSystemStream->addModule(new SpawnParticleSystemStreamModule);

	particleSystemStream->addModule(new InitialSizeParticleSystemStreamModule);
	particleSystemStream->addModule(new InitialColorParticleSystemStreamModule);
	particleSystemStream->addModule(new InitialLifeTimeParticleSystemStreamModule);
	particleSystemStream->addModule(new InitialVelocityParticleSystemStreamModule);

	particleSystemStream->addModule(new LifeSizeParticleSystemStreamModule);
	particleSystemStream->addModule(new LifeColorParticleSystemStreamModule);


	for (int i = 0; i < 100; i++) {
		particleSystemStream->update(0.1f);

		//particleSystemStream->

	}

}


void CoreModuleTest(Framework* framework) {

	CoreModule* coreModule = framework->findModule<CoreModule>();
	MemoryManager* memoryManager = coreModule->getMemoryManager();

	SharedPtr<MemoryBuffer> memoryBuffer1 = memoryManager->createBuffer(1024*1024);

}

void FileSystemManagerTest(Framework* framework) {

	unsigned long long mask;
	size_t size = sizeof(mask);
	CoreModule* coreModule = framework->findModule<CoreModule>();
	FileSystemManager* fileSystemManager = coreModule->getFileSystemManager();

	SharedPtr<File> file = fileSystemManager->createFile();

	char buffer[256];
	for (int i = 0; i < 256; i++) buffer[i] = 0;

	//file->open("TestFile.dat", FileAccessType::Read);
	//file->write(256, buffer);
	//file->close();
	file->open("TestFile.dat", FileAccessType::Read, true);	
	file->close();


	DynamicArray<FileName> fileNames;
	fileSystemManager->collectFiles(String("Content/Textures"), String("dds"), fileNames, true);
	DynamicArray<SharedPtr<MemoryBuffer>> fileBuffers;
	for(uint32_t i = 0; i < fileNames.size(); i++) {
		MemoryBuffer* buffer = fileSystemManager->loadFile(fileNames[i]);
		//fileBuffers.add(SharedPtr<MemoryBuffer>(buffer));
		fileBuffers.add(buffer);
	}
	int i = 0;

}

struct MaterialShaderPermutaion {

	union {
		//uint64_t mask;
		unsigned long long mask;
	};

	struct {
		bool diffuseMap1 : 1;
		bool normalMap1 : 1;
	};

};

void MaterialShaderTestTest(Framework* framework) {

	MaterialShaderPermutaion msp;

	Material* material = nullptr;
	if (material->getTexture(MaterialTextureType::Diffuse)) {

	}

	if (material->getTexture(MaterialTextureType::Normal)) {

	}

}

void MaterialTest(Framework* framework) {

	RenderModule* renderModule = framework->findModule<RenderModule>();
	MaterialManager* materialManager = renderModule->getMaterialManager();
	TextureManager* textureManager = renderModule->getTextureManager();
	SharedPtr<Texture> texture1 = textureManager->createTexture("Content/Textures/cats.dds");
	SharedPtr<Texture> texture2 = textureManager->createTexture("Content/Textures/cats.dds");
	SharedPtr<Texture> texture3 = textureManager->createTexture("Content/Textures/cookie.dds");
	SharedPtr<Texture> texture4 = textureManager->createTexture("Content/Textures/particle.dds");
	SharedPtr<Texture> texture5 = textureManager->createTexture("Content/Textures/betalbedo.dds");
	SharedPtr<Texture> texture6 = textureManager->createTexture("Content/Textures/BetNormalMap.dds");
	
	SharedPtr<Material> material1 = materialManager->createMaterial();

	material1->setTexture(texture1, MaterialTextureType::Default);
	material1->setTexture(texture3, MaterialTextureType::Detail);

	//material1->

	//material1->setTexture(texture4, MaterialTextureType::Emission);

	const Name skinLayerName("SkinLayer");
	material1->addMaterialLayer(skinLayerName);

	MaterialLayer* skinLayer = material1->getMaterialLayer(skinLayerName);
	check(skinLayer);

	material1->setTexture(texture4, MaterialTextureType::Detail, skinLayer);

	const Name shellacLayerName("ShellacLayer");
	material1->addMaterialLayer(shellacLayerName);
	MaterialLayer* shellacLayer = material1->getMaterialLayer(shellacLayerName);
	material1->setTexture(texture6, MaterialTextureType::Normal, shellacLayer);

	int i = 0;

}


void XML_Test(XMLNode* node) {

}

struct RC {};

class XRenderer {

	void virtual renderParticles(const RC&) {}
	void virtual renderTerrain(const RC&) {}
	void virtual renderModels(const RC&) {}

public:

};

}


class RenderResource {

};


struct HardwareTextureInfo {

};


class HardwareTexture : public RenderResource {

};

class HardwareSampler : public RenderResource {

};

class FrameBuffer : public RenderResource {

};

class SwapChain: public RenderResource {

};

class RenderTask {
};

class DrawTask : public RenderTask {
	virtual void setScissor() = 0;
};

class ComputeTask : public RenderTask {
};


class RenderContext {

public:

	virtual DrawTask* createDrawTask() = 0;

};

//class Pass : public Referenceable {
class Pass {
public:
	//BlendState blendState;
	uint32_t blendState;
	uint32_t depthStencilState;
	uint32_t ratesterState;
};

//class Technique : public Referenceable {
class Technique {
public:
	Pass* addPass() { return new Pass(); }
};





class Renderer {

public:

	virtual HardwareTexture* createTexture() = 0;
	virtual void destroyTexture(HardwareTexture*) = 0;

	virtual FrameBuffer* createFramebuffer(HardwareTexture* depthStencil, HardwareTexture* color0) = 0;
	virtual void destroyFramebuffer(FrameBuffer*) = 0;

	virtual SwapChain* createSwapChain() = 0;
	virtual void destroySwapChain(SwapChain*) = 0;


};










class Propertyable {

public:

	virtual void onChangeProperty() {}

};


class PropertyTest : public Propertyable {

public:
	
	void setup() {
	
	
	}

};


/*
История повторяется четыре раза: 1-ый  раз - как трагедия, 2-ой раз - в виде фарса, 3-ий раз - для особо тупых и 4-ый раз - на Украине
*/
