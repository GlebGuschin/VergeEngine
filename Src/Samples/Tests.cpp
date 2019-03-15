#include "World.hpp"
#include "Common.hpp"
#include "DynamicArray.hpp"
#include "Math.hpp"
#include "Color.hpp"
#include "Name.hpp"
#include "ParticleSystemComponent.hpp"
#include "LightComponent.hpp"
#include "CameraComponent.hpp"




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

}