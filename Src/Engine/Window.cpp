#include "Window.hpp"
#include "InputModule.hpp"

namespace Verge3D {

HINSTANCE Window::hInstance = NULL;
Window::ClassMapType Window::ClassMap;
Window::WindowMapType Window::WindowMap;

MouseButtonType ParseMouseButton(UINT message) {

	MouseButtonType type;
	
	switch (message) {

		case WM_LBUTTONUP:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
			type = MouseButtonType::Left;
			break;

		case WM_RBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONDBLCLK:
			type = MouseButtonType::Right;
			break;

		case WM_MBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONDBLCLK:
			type = MouseButtonType::Middle;
			break;

		default: 
			assert(0); break;

	};

	return type;

}

bool Window::RegisterWindowClass(WNDPROC lpfnWndProc, LPCWSTR lpszClassName) {

		std::wstring wstr = lpszClassName;

		ClassMapType::iterator it = ClassMap.find(wstr);
		if (it != ClassMap.end()) {
			it->second.rc++;
			return(true);
		}

		check(hInstance);

		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wcex.lpfnWndProc = lpfnWndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = lpszClassName;
		//wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
		wcex.hIconSm = NULL;

		ATOM atom = RegisterClassEx(&wcex);

		check(atom);

		Atom a;
		a.atom = atom;
		a.rc = 1;

		ClassMap.insert(ClassMapType::value_type(wstr, a));

		return true;

}

void Window::AddWindow(HWND hWnd, Window* window) {
	
	check(WindowMap.find(hWnd) == WindowMap.end());
	WindowMap.insert(WindowMapType::value_type(hWnd,window));

}

void Window::RemoveWindow(HWND hWnd) {

	check(WindowMap.find(hWnd) != WindowMap.end());
	WindowMap.erase(WindowMap.find(hWnd));

}

Window* Window::GetWindow(HWND hWnd) {

	WindowMapType::iterator it = WindowMap.find(hWnd);
	if(it != WindowMap.end()) return it->second;
	return NULL;
}

Framework* gFramework = nullptr;

void Window::SetFramework(Framework* framework) {
	gFramework = framework;
}

Framework* Window::GetFramework() {
	return gFramework;
}



LRESULT  Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	Window* window = GetWindow(hWnd);
	//if(window==NULL) return 0;

	int xPos = LOWORD(lParam);
	int yPos = HIWORD(lParam);
	int wheelValue = GET_WHEEL_DELTA_WPARAM(wParam);
	const MousePosition mousePosition(xPos,yPos);
	const WindowSize windowSize(xPos, yPos);

	switch (message) {

		case WM_COMMAND:

			//wmId = LOWORD(wParam);
			//wmEvent = HIWORD(wParam);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	
		case WM_PAINT:
			if(window) {
				window->onPaint();
			}				 
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_MOUSEWHEEL:
			if(window) {
				window->onMouseWheel(mousePosition, GET_WHEEL_DELTA_WPARAM(wParam));
			}
			break;

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
			if(window) {
				window->onMouseButton(mousePosition, ParseMouseButton(message), InputActionType::Press);
			}
			break;

		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			if(window) {
				window->onMouseButton(mousePosition, ParseMouseButton(message), InputActionType::Release);
			}
			break;

		case WM_LBUTTONDBLCLK:
			if(window) {
				window->onMouseButton(mousePosition, ParseMouseButton(message), InputActionType::Double);
			}
			break;
		
		case WM_MOUSEMOVE:
			if(window) {
				window->onMouseMove(mousePosition);
			}			
			break;
		
		case WM_CHAR:
			/*
			if (GetFramework()) {
				KeyboardEvent ke;
				ke.type = (KeyType)wParam;
				GetFramework()->findModule<InputModule>()->processKeyboardEvent(ke);
			}
			*/
			break;

		case WM_KEYUP:	
			if(window) {
				if (GetFramework()) {
					KeyboardEvent ke;
					ke.action = InputActionType::Release;
					ke.type = (KeyType)wParam;
					GetFramework()->findModule<InputModule>()->processKeyboardEvent(ke);
				}				
			}
			break;

		case WM_KEYDOWN:	
			if(window) {
				if (GetFramework()) {
					KeyboardEvent ke;
					ke.action = InputActionType::Press;
					ke.type = (KeyType)wParam;
					GetFramework()->findModule<InputModule>()->processKeyboardEvent(ke);
				}
			}
			break;

		case WM_SYSKEYDOWN:
			if(window) {
				//window->onKeyboard((KEY_TYPE)wParam, INPUT_ACTION_PRESS,0);
			}
			//gFramework->processKeyboard((unsigned)wParam);
			break;

		case WM_SIZE:
			if (window) {
				window->onResize(WindowSize(xPos,yPos));
			}
			break;

		case 55:
			break;

		default:

			int i = 10;

			return DefWindowProc(hWnd, message, wParam, lParam);

	}

	return 0;
}



void Window::create(const WindowInfo& info_) {

	info = info_;

	const bool registered = RegisterWindowClass(getClassFunc(), getClassName());

	UINT windowStyle = 0;
	if (info.type == WindowType::Main) windowStyle = WS_OVERLAPPEDWINDOW;

	if (info.type == WindowType::Child) {
		//windowStyle = WS_CHILD | WS_THICKFRAME;
		windowStyle = WS_CHILD;
	}

	if (registered) {
		hWnd = CreateWindowW(	getClassName(), 
								getWindowName(),
								windowStyle, 
								0, 0, 
								info.size.width, 
								info.size.height, 
								info.hParentWnd,
								NULL, 
								hInstance, 
								NULL);
		AddWindow(hWnd, this);
	}

}

void Window::create() {

	//info = info_;
	info.size.width = 800;
	info.size.height = 600;
	info.type = WindowType::Main;

	create(info);

}

void Window::destroy() {

	RemoveWindow(hWnd);	
	DestroyWindow(hWnd);

}

void Window::setVisible(bool visible_) {

	visible = visible_;
	ShowWindow(hWnd, visible ? TRUE : FALSE);

}

void Window::show() {
	setVisible( true );
}

void Window::hide() {
	setVisible(false);
}

void Window::update() {
	UpdateWindow(hWnd);
}

/*
WindowClientRect Window::getWindowClientRect() {

	RECT rect;
	GetClientRect(hWnd, &rect);
	return ClientWindowSize(rect.)
}
*/

void Window::resize(int x, int y) {

	info.size = WindowSize(x, y);
	MoveWindow(hWnd, info.position.x, info.position.y, info.size.width, info.size.height, TRUE);
}

void Window::move(int x, int y) {

	info.position.x = x;
	info.position.y = y;

	MoveWindow(hWnd, x,y, info.size.width, info.size.height, TRUE);

}

void Window::addListener(WindowListener* listener) {

	listeners.add(listener);

}

void Window::removeListener(WindowListener* listener) {

	listeners.remove(listener);

}


void Window::onMouseButton(const MousePosition& mousePosition, MouseButtonType buttonType, InputActionType actionType) {

	switch (actionType) {
		case InputActionType::Press:
			DebugLog("Press mouse(%i,%i)", mousePosition.x, mousePosition.y); 
			break;

		case InputActionType::Release:
			DebugLog("Release mouse(%i,%i)", mousePosition.x, mousePosition.y);
			break;

		case InputActionType::Double:
			DebugLog("Double mouse(%i,%i)", mousePosition.x, mousePosition.y); 
			break;
	};

}

/*
void Window::onKeyboard(KEY_TYPE buttonType, INPUT_ACTION_TYPE actionType, unsigned modificators ) {
	int i = 0;
}

*/

void Window::onMouseWheel(const MousePosition& mousePosition, int value) {

	DebugLog("Window::onMouseWheel(%i,%i,%i)", mousePosition.x, mousePosition.y, value);

}

void Window::onMouseMove(const MousePosition& mousePosition) {

	DebugLog("Mouse move(%i,%i)", mousePosition.x, mousePosition.y); 

}

void Window::onResize(const WindowSize& windowSize) {

	for (size_t i = 0; i < listeners.size(); i++) {
		listeners[i]->onResize(this, windowSize);
	}

	DebugLog("Window id=%u, size %u,%u", hWnd, windowSize.width, windowSize.height);
}

void Window::onPaint() {

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	for (size_t i = 0; i < listeners.size(); i++) {
		listeners[i]->onPaint(this);
	}
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

	RECT rect;
	rect.left = rect.top = 0;
	rect.right = 100;
	rect.bottom = 100;

	DrawTextA(hdc, "asdasd", 0, &rect, 0);


	EndPaint(hWnd, &ps);

}

}