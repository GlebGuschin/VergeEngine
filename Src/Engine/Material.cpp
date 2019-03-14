#include "Material.hpp"
#include "MaterialManager.hpp"

namespace Verge3D {

Material::~Material() {

	manager->destroyMaterial(this);

}

void Material::reloadFromAsset() {

	if (!asset) {
		return;
	}



}


}
