#include "LightComponent.hpp"

namespace Verge3D {


void LightComponent::setColor(const Color& color_) { 

	color = color_; 

}
const Color& LightComponent::getColor() const { 

	return color; 

}


}