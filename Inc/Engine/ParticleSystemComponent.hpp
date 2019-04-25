#pragma once

#include "Component.hpp"
#include "ParticleSystem.hpp"

namespace Verge3D {

class ParticleSystemComponent : public Component {
public:

	virtual void setParticleSystem(ParticleSystem*) {}

};

}
