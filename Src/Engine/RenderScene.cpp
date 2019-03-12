#include "RenderScene.hpp"

using namespace Verge3D;


void RenderSceneObject::addListener(RenderSceneObjectListener*listener) {

	listeners.add(listener);

}

void RenderSceneObject::removeListener(RenderSceneObjectListener*listener) {

	listeners.remove(listener);

}

void RenderSceneObject::setTransform(const Transform& transform_) {


}


void DebugRenderSceneObject::addLine(const Vector& v0, const Vector& v1, const Color& c) {

	DebugRenderItem item;
	item.type = DebugRenderType::Line;
	items.push_back(item);

}

void DebugRenderSceneObject::addWiredCube(const Vector& origin, const Vector& size, const Color& c) {

}

void DebugRenderSceneObject::addSolidCube(const Vector& origin, const Vector& size, const Color& c) {

}

void DebugRenderSceneObject::addWireSphere(const Vector& origin, const float radius, const Color& c) {

}

void DebugRenderSceneObject::addSolidSphere(const Vector& origin, const float radius, const Color& c) {
}



void RenderScene::addObject(RenderSceneObject* object) {

	objects.add(object);

}

void RenderScene::removeObject(RenderSceneObject* object) {

	objects.remove(object);

}


ParticleSystemRenderSceneObject* RenderScene::createParticleSystem() {

	ParticleSystemRenderSceneObject* p = new ParticleSystemRenderSceneObject(nullptr);

	addObject(p);
	return p;

}

void RenderScene::destroyParticleSystem(ParticleSystemRenderSceneObject* p) {

	removeObject(p);
	delete p;

}


DebugRenderSceneObject* RenderScene::createDebug() {

	DebugRenderSceneObject* d = new DebugRenderSceneObject(nullptr);
	addObject(d);
	return d;
}

void RenderScene::destroyDebug(DebugRenderSceneObject* d) {

	removeObject(d);
	delete d;

}


void RenderScene::update(float deltaTime) {

}

void RenderScene::onChangeTransform(RenderSceneObject*) {

}

// https://www.youtube.com/watch?v=cT2lMLOOiec&t=146s
// c40a351c7a69bb825a463ec3f46ce2447b0aa245