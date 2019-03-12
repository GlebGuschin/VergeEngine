#pragma once

#include "RenderCommon.hpp"

namespace Verge3D {


class ParticleSystemStream;


class Particle {

	float lifeTime, lifeTimeMax;
	Vector position;
	Vector velocity;
	Vector baseVelocity;
	Vector linearAcceleration;
	Color color;
	float size;
	//bool dead;

public:

	Particle() : lifeTimeMax(FLT_MAX), lifeTime(FLT_MAX), size(1.0f) {}

	float getTimeScale() const { return lifeTime / lifeTimeMax; }

	void update(float deltaTime) {

		lifeTime += deltaTime;

		if (lifeTime >= lifeTimeMax) {
			kill();
		}
		else {
			velocity += linearAcceleration * deltaTime;
			position += velocity * deltaTime;
		}

	}

	void reset() {
	}

	void kill() {
		lifeTime = lifeTimeMax;
	}

	bool isDead() const {
		return lifeTime >= lifeTimeMax;
	}

	void setColor(const Color& color_) {
		color = color_;
	}

	void setSize(float value) {
		size = value;
	}

	float getSize() const {
		return size;
	}

	void applySizeScale(float scale) {
		size *= scale;
	}

	void setLifeTime(float value) {
		lifeTime = value;
	}

	float getLifeTime() const {
		return lifeTime;
	}

	float getLifeTimeMax() const {
		return lifeTimeMax;
	}

	void setLifeTimeMax(float time_) {
		lifeTimeMax = time_;
	}

	void setVelocity(const Vector& velocity_) {
		velocity = velocity_;
	}

	const Vector& getVelocity() const {
		return velocity;
	}

	void setPosition(const Vector& position_) {
		position = position_;
	}

};

inline bool ParticleComparatorByLifeTime(const Particle& l, const Particle& r) {

	return l.getLifeTime() < r.getLifeTime();
}


#define MAX_PARTICLES 64

class ParticleStorage : public Referenceable {

	//Particle particles[MAX_PARTICLES];
	std::vector<Particle> particles;
	//size_t  numAliveParticles;

public:

	ParticleStorage() { 
		particles.reserve(MAX_PARTICLES);
		clear(); 
	}

	void update(float deltaTime);
	void clear();

	const Particle& getParticle(unsigned index) const { return particles[index]; }
	Particle& getParticle(unsigned index) { return particles[index]; }
	size_t getNumParticles() const { return particles.size(); };

	Particle* const spawn();
	void compact();

};



enum class ParticleDistributionType {
	Const,
	Random
};

template <typename T>
class ParticleDistribution {
	ParticleDistributionType type;
	T value;
	T minValue, maxValue;
public:
	ParticleDistribution(const T&value_) : type(ParticleDistributionType::Const), value(value_) {}
	ParticleDistribution(const T&minValue_, const T&maxValue_) : type(ParticleDistributionType::Random), minValue(minValue_), maxValue(maxValue_) {}

	T getValue(float time) const {
		T retValue = value;
		switch (type) {
			case ParticleDistributionType::Const:
				break;

			case ParticleDistributionType::Random:
			{
				const float r = Random(0.0f,1.0f);
				retValue = Lerp(minValue, maxValue, r);
			}
			break;
		};

		return retValue;
	}
};

struct FloatParticleModuleDistributionParam {
	bool baked;
	ParticleDistribution<float> distribution;
	FloatParticleModuleDistributionParam() : distribution(0.0f, 1.0f) {}
};

struct VectorParticleModuleDistributionParam {
	bool baked;
	ParticleDistribution<Vector> distribution;
	VectorParticleModuleDistributionParam() : distribution(Vector(-1, -1, -1), Vector(1, 1, 1)) {}
};


struct SpawnParticleInfo {
	Particle* const particle;
	float totalTime, deltaTime;
	SpawnParticleInfo(Particle* const particle_) : particle(particle_) {}
};

struct UpdateParticlesInfo {
	ParticleStorage* const storage;
	float totalTime, deltaTime;
	UpdateParticlesInfo() : storage(nullptr), totalTime(0.0f), deltaTime(0.0f) {}
	UpdateParticlesInfo(ParticleStorage* const storage_) : storage(storage_) {}
};


class ParticleSystemStreamModule : public Referenceable {
	
	bool spawnModule;
	bool updateModule;

	//ParticleStorage* storage;

public:

	ParticleSystemStreamModule(bool spawnModule_, bool updateModule_) : spawnModule(spawnModule_), updateModule(updateModule_){}

	virtual void onSpawnParticle(const SpawnParticleInfo&) {}
	virtual void onUpdateParticles(const UpdateParticlesInfo&) {}

	bool isSpawnModule() const { return spawnModule; }
	bool isUpdateModule() const { return updateModule; }

};

class SpawnParticleSystemStreamModule : public ParticleSystemStreamModule {

	FloatParticleModuleDistributionParam rate;

public:

	SpawnParticleSystemStreamModule() : ParticleSystemStreamModule(true, false) {
		rate.distribution = ParticleDistribution<float>(0.5f);
	}

	//void onSpawnParticle(Particle* const, const float spawnTime);
	//void onUpdateParticles(ParticleStorage* const) {}

	const FloatParticleModuleDistributionParam& getRate() const { return rate; };
	void setRate(const FloatParticleModuleDistributionParam& rate_) { rate = rate_; };

};

class InitialColorParticleSystemStreamModule : public ParticleSystemStreamModule {

public:

	InitialColorParticleSystemStreamModule() : ParticleSystemStreamModule(true, false) {}

	void onSpawnParticle(const SpawnParticleInfo&);
};


class InitialSizeParticleSystemStreamModule : public ParticleSystemStreamModule {

	FloatParticleModuleDistributionParam size;

public:

	InitialSizeParticleSystemStreamModule() : ParticleSystemStreamModule(true, false) {}

	void onSpawnParticle(const SpawnParticleInfo&);
};


class InitialLifeTimeParticleSystemStreamModule : public ParticleSystemStreamModule {

	FloatParticleModuleDistributionParam lifeTime;

public:

	InitialLifeTimeParticleSystemStreamModule() : ParticleSystemStreamModule(true, false) {
		lifeTime = FloatParticleModuleDistributionParam();
	}

	void onSpawnParticle(const SpawnParticleInfo&);
};


class LifeColorParticleSystemStreamModule : public ParticleSystemStreamModule {

public:

	LifeColorParticleSystemStreamModule() : ParticleSystemStreamModule(false, true) {
	
	}
	
	void onUpdateParticles(const UpdateParticlesInfo&);
};

class LifeSizeParticleSystemStreamModule : public ParticleSystemStreamModule {

	FloatParticleModuleDistributionParam size;

public:

	LifeSizeParticleSystemStreamModule() : ParticleSystemStreamModule(true, false) {}
	
	void onUpdateParticles(const UpdateParticlesInfo&);
};


class InitialVelocityParticleSystemStreamModule : public ParticleSystemStreamModule {

	VectorParticleModuleDistributionParam velocity;

public:

	InitialVelocityParticleSystemStreamModule() : ParticleSystemStreamModule(true, false) {}

	void onSpawnParticle(const SpawnParticleInfo&);
};







class ParticleSystemLevelOfDetail : public Referenceable {

	SharedPtr<ParticleStorage> storage;

};

class ParticleSystemStream : public Referenceable {

	DynamicArray<SharedPtr<ParticleSystemStreamModule>> modules;

	SharedPtr<ParticleStorage> storage;

	float totalTime;
	float spawnTime, spawnTimeMax;
	float repeatTime, repeatTimeMax;

	SpawnParticleSystemStreamModule* getSpawnModule() const;

public:

	ParticleSystemStream() : 
		totalTime(0),
		spawnTime(0), 
		spawnTimeMax(0) {
		storage = new ParticleStorage;
		addModule( new SpawnParticleSystemStreamModule);
	}

	void reset();

	void addModule(ParticleSystemStreamModule* module);

	void update(float deltaTime);

};






class ParticleSystem : public Referenceable {

public:

	ParticleSystemStream* createStream();

};


}