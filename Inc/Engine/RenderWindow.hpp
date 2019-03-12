#pragma once

#include "Window.hpp"
#include "RenderModule.hpp"


namespace Verge3D {

class RenderWindow : public Window {

	LPCWSTR getClassName() const { return(L"RenderWindow"); }
	SharedPtr<RenderContext> renderContext;

	void onPaint();
	void onResize(const WindowSize&);
	//Framework*  framework;

public:

	RenderWindow() : renderContext(nullptr) {}
	~RenderWindow() {
		int i = 0;
	}

	//void create(Window* parent);
	//void _setFramework(Framework* framework_) { framework = framework_; }

	void setRenderContext(RenderContext* renderContext_) { renderContext = renderContext_; }

	RenderContext* getRenderContext() const { return renderContext; }
	

	virtual LPCWSTR getWindowName() const { return(L"RenderWindow"); };
};

}