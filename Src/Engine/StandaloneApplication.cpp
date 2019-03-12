#include "StandaloneApplication.hpp"
//#include "RenderSystem.hpp"

using namespace Verge3D;

int StandaloneApplication::mainLoop() {

	MSG msg;
	HACCEL hAccelTable = 0;

	do {

			if (!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

				onUpdate();

			} else {

				if (msg.message == WM_PAINT) {
					onUpdate();
					//gFramework->refresh();
					//update();             
				}

				if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE) {
					break;
				}


				if (msg.message == WM_QUIT) {
					break;
				}

				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {

					TranslateMessage(&msg);
					DispatchMessage(&msg);

				}

			}
			
			/*
			if (isClosed()) {
				break;
			}
			*/
			
	} while (1);

	return 0;

}

void StandaloneApplication::onUpdate() {

	getFramework()->tick();

}

void StandaloneApplication::onExit() {

	getFramework()->findModule<InputModule>()->removeListener(this);

	mainWindow->removeListener(this);
	
	mainWindow->destroy();

	Window::SetFramework(nullptr);
}

//#include "RenderScene.hpp"

void StandaloneApplication::onStart() {

	Window::SetInstance(hInstance);
	Window::SetFramework(getFramework());

	getFramework()->findModule<InputModule>()->addListener(this);
	
	mainWindow = new MainWindow;
	mainWindow->create();

	mainWindow->addListener(this);

	mainWindow->show();
	mainWindow->move(10, 10);
	mainWindow->resize(800, 600);	

}


void StandaloneApplication::onPaint(Window*) {

	int i = 0;
	//getFramework()->findModule<RenderSystem>()->beginFrame(renderContext);
	//getFramework()->findModule<RenderSystem>()->endFrame();

}

void StandaloneApplication::onResize(Window* window, const WindowSize& windowSize) {

	/*
	if (renderContext) {
		renderContext->setSize(windowSize);
		DebugLog("Window id=%u, size %u,%u", window, windowSize.width, windowSize.height);
	}
	int i = 0;
	*/
}


