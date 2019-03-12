#pragma once

#include "StandaloneApplication.hpp"
#include "RenderWindow.hpp"

namespace Verge3D {


class TestApplication : public StandaloneApplication {

protected:
	
	SharedPtr<RenderWindow> renderWindow;
	
	void onStart();
	void onExit();
	void onUpdate();

	void onPaint(Window*) {}
	void onResize(Window*, const WindowSize&);

	void onKeyboardAction(const KeyboardEvent&);

public:
	
};


}


