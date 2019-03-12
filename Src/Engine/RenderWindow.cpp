#include "RenderWindow.hpp"

using namespace Verge3D;

void RenderWindow::onResize(const WindowSize& windowSize) {

	if (renderContext) {
		renderContext->setSize(windowSize);
	}

}

void RenderWindow::onPaint() {


	RenderModule* rm = Window::GetFramework()->findModule<RenderModule>();
	rm->beginFrame(getRenderContext());
	rm->endFrame();
	return;

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	RECT rect;
	rect.left = rect.top = 0;
	rect.right = 100;
	rect.bottom = 100;

	DrawTextA(hdc, "asdasd", 0, &rect, 0);


	/*
	if( gRenderModule ) {
			gRenderModule->beginFrame();
			gRenderModule->endFrame();
	}
	*/

	/*
	if(GetRenderer()) {
			GetRenderer()->beginFrame();
			GetRenderer()->endFrame();
	}
	*/

	EndPaint(hWnd, &ps);

}