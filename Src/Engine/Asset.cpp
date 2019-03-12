#include "Asset.hpp"

namespace Verge3D {


void Asset::addListener(AssetListener* listener) {

	listeners.add(listener);
}

void Asset::removeListener(AssetListener* listener) {

	listeners.remove(listener);
}


}