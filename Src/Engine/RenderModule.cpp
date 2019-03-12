#include "RenderModule.hpp"

namespace Verge3D {

RenderScene* RenderModule::createScene() {

	return new RenderScene;
}

void RenderModule::destroyScene(RenderScene* renderScene) {

	delete renderScene;
}

void RenderModule::drawScene(RenderScene*, const SceneView&) {
}

}
