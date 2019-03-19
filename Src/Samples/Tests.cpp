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




namespace Verge3D {

void WorldTest() {

	
	SharedPtr<World> world = new World;

	
	Entity* entity1 = new Entity;
	Entity* entity11 = new Entity;
	Entity* entity111 = new Entity;
	Entity* entity2 = new Entity;

	entity111->addComponent(new ParticleSystemComponent);
	entity111->addComponent(new OmniLightComponent);
	entity1->addComponent(new CameraComponent);

	
	

	world->spawnEntity(entity1);
	world->spawnEntity(entity11, entity1);
	world->spawnEntity(entity111, entity11);
	world->spawnEntity(entity2);


	
	world->dump();

	world->destroyEntity(entity1);

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

	SharedPtr<MemoryBuffer> memoryBuffer1 = memoryManager->createMemoryBuffer(1024*1024);


}

}