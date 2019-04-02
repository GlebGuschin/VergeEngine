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






class Pass : public Referenceable {

public:

	//BlendState blendState;
	uint32_t blendState;
	uint32_t depthStencilState;
	uint32_t ratesterState;

};


class Technique : public Referenceable {

public:

	Pass* addPass();

};





}
