#pragma once

#include "Component.hpp"

#include "Color.hpp"

namespace Verge3D {

class LightComponent : public Component {

		Color color;

public:

		void setColor(const Color& color_);
		const Color& getColor() const;

};


class DirectionalLightComponent : public LightComponent {

public:

};

class OmniLightComponent : public LightComponent {

public:

};

class SpotLightComponent : public LightComponent {

public:

};

class AreaLightComponent : public LightComponent {

public:

};


}
