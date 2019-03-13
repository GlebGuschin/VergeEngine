#pragma once

#include "Module.hpp"
#include "RenderCommon.hpp"
#include "RenderScene.hpp"
#include "TextureManager.hpp"
#include "MaterialManager.hpp"
#include <Windows.h>

namespace Verge3D {

struct SceneView;

struct RenderContextInfo {
	WindowSize size;
	int format;
	HWND hWnd;
	RenderContextInfo() : size(800, 600) {}
};

class RenderContext : public Referenceable {
	RenderContextInfo info;
public:

	RenderContext(const RenderContextInfo info_) : info(info_) {}
	virtual bool setSize(const WindowSize&) { return false; }

};


class RenderModule : public Module {

protected:
	RenderContext* currentRenderContext;
	TextureManager* textureManager;
	MaterialManager* materialManager;

public:

	RenderModule() : Module("RenderModule") {
	
	}

	virtual bool init(Framework* framework_) { 
		Module::init(framework_); 
		textureManager = new TextureManager(this);
		materialManager = new MaterialManager(this);
		return true; 
	}

	virtual void shutdown() {
		delete materialManager;
		delete textureManager;
	}

	virtual void update(float td) {}


	virtual RenderContext* createRenderContext(const RenderContextInfo&) = 0;
	virtual void destroyRenderContext(RenderContext*) = 0;
	virtual void beginFrame(RenderContext*) = 0;
	virtual void endFrame() = 0;

	virtual RenderScene* createScene();
	virtual void destroyScene(RenderScene*);


	virtual void drawScene(RenderScene*, const SceneView&);

	TextureManager* getTextureManager() const { return textureManager; }
	MaterialManager* getMaterialManager() const { return materialManager; }
	

};

RenderModule* CreateRenderModule();	


}

/*
	{
		// gleb
		FRHIAsyncComputeCommandListImmediate& RHICmdListComputeImmediate = FRHICommandListExecutor::GetImmediateAsyncComputeCommandList();
		FName name("Test");
		SCOPED_COMPUTE_EVENT(RHICmdListComputeImmediate, name);
	}

*/