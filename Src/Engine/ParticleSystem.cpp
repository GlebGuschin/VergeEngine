#include "ParticleSystem.hpp"

namespace Verge3D {

void ParticleStorage::update(float deltaTime) {

	bool needCompact = false;
	uint32_t deadCount = 0;

	for (size_t i = 0; i < particles.size(); i++) {

		/*
		Particle& particle = particles[i];
		const float time = particle.getLifeTime() + deltaTime;

		if (time >= particle.getLifeTime()) {
			particle.kill();
			needCompact = true;
			deadCount++;
			continue;
		}	
		particle.setLifeTime(time);
		*/

		Particle& particle = particles[i];
		particle.update(deltaTime);


	}

	/*
	if (needCompact) {
		DebugLog("deadCount= %u", deadCount);
		compact();
	}
	*/

	compact();

}

void ParticleStorage::clear() {
	
	for (size_t i = 0; i < particles.size(); i++) {
		particles[i] = Particle();
	}

}

Particle* const ParticleStorage::spawn() {
	
	if (particles.size() >= MAX_PARTICLES) {
			DebugLog("Particle storage is overload!");
	}

	particles.push_back(Particle());
	return &particles[particles.size()-1];


	/*
	if (!particles.size()) {
		particles.push_back(Particle());
		return &particles[0];
	}

	for (size_t i = numAliveParticles; i < particles.size(); i++) {
		numAliveParticles++;
		if (particles[i].isDead()) {
			particles[i].setLifeTime(0);
			numAliveParticles = i + 1;
			return &particles[i];
		}
	}
	*/
	return nullptr;
}

void ParticleStorage::compact() {
	//std::sort(&particles[0], &particles[MAX_PARTICLES], ParticleComparatorByLifeTime);
	//std::sort(particles.begin(), particles.end(), ParticleComparatorByLifeTime);

	auto it	= std::remove_if(particles.begin(), particles.end(), [](Particle& p) { return p.getLifeTime() >= p.getLifeTimeMax(); });
	particles.erase(it, particles.end());

	//numAliveParticles = particles.size();

}

void InitialColorParticleSystemStreamModule::onSpawnParticle(const SpawnParticleInfo& info) {

	info.particle->setColor(Color(Random(0,1), Random(0, 1), Random(0, 1), 0.5 ));

}

void InitialSizeParticleSystemStreamModule::onSpawnParticle(const SpawnParticleInfo& info) {

	info.particle->setSize(size.distribution.getValue(info.totalTime));

}

void InitialLifeTimeParticleSystemStreamModule::onSpawnParticle(const SpawnParticleInfo& info) {

	info.particle->setLifeTimeMax(lifeTime.distribution.getValue(info.totalTime));
	info.particle->setLifeTime(0);
	
}


/*

void SpawnParticleSystemStreamModule::onSpawnParticle(Particle* const, const float spawnTime) {


}

InitialColorParticleSystemStreamModule() : ParticleSystemStreamModule(true, false) {}

void onSpawnParticle(Particle* const, const float spawnTime);

void InitialColorParticleSystemStreamModule::onSpawnParticle(Particle* const particle, const float spawnTime) {

	float f = Random(0.0f, 1.0f);

	particle->setColor(Color());

}

*/

void LifeColorParticleSystemStreamModule::onUpdateParticles(const UpdateParticlesInfo& info) {

	for (uint32_t i = 0; i < info.storage->getNumParticles(); i++) {

		info.storage->getParticle(i).setColor(Color());
	}

}

void LifeSizeParticleSystemStreamModule::onUpdateParticles(const UpdateParticlesInfo& info) {

	const float scale = size.distribution.getValue(info.totalTime);

	for (uint32_t i = 0; i < info.storage->getNumParticles(); i++) {

		info.storage->getParticle(i).applySizeScale(scale);
	}

}



void InitialVelocityParticleSystemStreamModule::onSpawnParticle(const SpawnParticleInfo& info) {

	info.particle->setVelocity(Random(Vector(-1,-1,-1), Vector(1,1,1)));

	//Random(Color(), Color());

}












void ParticleSystemStream::addModule(ParticleSystemStreamModule* module) {

	modules.add(module);

}

void ParticleSystemStream::update(float deltaTime) {

	totalTime += deltaTime;

	storage->update(deltaTime);

	
	for (uint32_t i = 0; i < modules.size(); i++) {

		ParticleSystemStreamModule* p = modules[i];

		if (p->isUpdateModule()) {
			UpdateParticlesInfo info(storage);
			//info.storage = storage;
			info.deltaTime = deltaTime;
			p->onUpdateParticles(info);

		}

	}


	uint32_t numParticlesToSpawn = 0;
	auto spawnModule = getSpawnModule();
	spawnTimeMax = 1.0f / spawnModule->getRate().distribution.getValue(totalTime);
	spawnTime += deltaTime;
	

	if (spawnTime >= spawnTimeMax) {
		numParticlesToSpawn = floor(spawnTime / spawnTimeMax);
	}
	
	for (uint32_t i = 0; i < numParticlesToSpawn; i++) {

		Particle* const particle = storage->spawn();
		if (!particle) break;

		for (uint32_t i = 0; i < modules.size(); i++) {

			ParticleSystemStreamModule* p = modules[i];

			if (p->isSpawnModule()) {
				SpawnParticleInfo info(particle);
				info.totalTime = totalTime;
				info.deltaTime = deltaTime;
				p->onSpawnParticle(info);	
			}

		}

	}

	int i = 0;

}

void ParticleSystemStream::reset() {

}

SpawnParticleSystemStreamModule* ParticleSystemStream::getSpawnModule() const {

	for (uint32_t i = 0; i < modules.size(); i++) {
		ParticleSystemStreamModule* p = modules[i];
		SpawnParticleSystemStreamModule* module = dynamic_cast<SpawnParticleSystemStreamModule*>(p);
		if (module) {
			return module;			
		}
		
	}

	return nullptr;

}

}