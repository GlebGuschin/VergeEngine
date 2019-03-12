#pragma once

#include "Application.hpp"
#include "Window.hpp"

namespace Verge3D {


class StandaloneApplication : public Application, public WindowListener {

protected:
	
	SharedPtr<MainWindow> mainWindow;

	int mainLoop();

	void onStart();
	void onExit();
	void onUpdate();

	void onPaint(Window*);
	void onResize(Window*, const WindowSize&);

	void onMouseAction(const MouseEvent&) {}
	void onKeyboardAction(const KeyboardEvent&) {}

public:
	

};


}


