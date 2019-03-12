#include "TestApplication.hpp"

using namespace Verge3D;

void TestApplication::onStart() {

	StandaloneApplication::onStart();

	RenderContextInfo rcInfo;
	RenderModule* rm = getFramework()->findModule<RenderModule>();

	renderWindow = new RenderWindow;
	WindowInfo renderWindowInfo;
	renderWindowInfo.hParentWnd = mainWindow->getHWND();
	renderWindowInfo.type = WindowType::Child;
	renderWindow->create(renderWindowInfo);

	rcInfo.hWnd = renderWindow->getHWND();
	renderWindow->setRenderContext(rm->createRenderContext(rcInfo));

	renderWindow->show();
	renderWindow->move(00, 00);
	renderWindow->resize(800, 600);
	renderWindow->update();

}

void TestApplication::onExit() {

	RenderModule* rm = getFramework()->findModule<RenderModule>();
	rm->destroyRenderContext(renderWindow->getRenderContext());

	renderWindow->destroy();
	StandaloneApplication::onExit();

}

void TestApplication::onUpdate() {

	StandaloneApplication::onUpdate();

}

void TestApplication::onResize(Window* window, const WindowSize& windowSize) {

	if (window == mainWindow && renderWindow) {
		RECT rect;
		GetClientRect(mainWindow->getHWND(), &rect);		
		renderWindow->resize(rect.right - rect.left, rect.bottom - rect.top);
		renderWindow->move(rect.left, rect.top);
		//(windowSize.width, windowSize.height);
	}

	if (renderWindow)
	{
		//GetClientRect(renderWindow->getHWND(), &rect);
		int i = 0;
	}

}

void TestApplication::onKeyboardAction(const KeyboardEvent& ke) {

	int i = 0;
	if (ke.type == KEY_H && ke.action == InputActionType::Release) {
		int i = 0;
	}

}
