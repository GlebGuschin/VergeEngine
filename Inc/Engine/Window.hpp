#pragma once

#include "Common.hpp"
#include "Math.hpp"
#include "DynamicArray.hpp"
#include "Framework.hpp"
#include "Input.hpp"

#include <Windows.h>


namespace Verge3D {


enum WindowType {
	Main,
	Child
};

class Window;
class WindowListener;


class WindowListener {

public:
	virtual void onPaint(Window*)=0;
	virtual void onResize(Window*, const WindowSize&) = 0;

};

struct WindowInfo {
	HWND hParentWnd;
	WindowPosition position;
	WindowType type;
	WindowSize size;
	//int width, height;
	WindowInfo() : size(800, 600), hParentWnd(NULL){}
};

class Window : public Referenceable {

protected:

	HWND hWnd;

	static HINSTANCE hInstance;
	DynamicArray<WindowListener*> listeners;

	bool	visible;
	bool	active;
	
	WindowInfo info;

	struct Atom {
		ATOM atom;
		unsigned rc;
		Atom() { atom = 0; rc = 0; }
	};

	typedef std::map<std::wstring, Atom> ClassMapType;
	static ClassMapType ClassMap;	
	typedef std::map<HWND, Window*> WindowMapType;
	static WindowMapType WindowMap;

	//LPCWSTR windowClass;
	
	virtual LPCWSTR getClassName() const { return(L"Window"); }
	virtual WNDPROC getClassFunc() const { return(&WndProc); };
	virtual LPCWSTR getWindowName() const { return(L"Window"); };

	virtual void onPaint();
	virtual void onResize(const WindowSize&);

	
	virtual void onMouseButton(const MousePosition& mousePosition, MouseButtonType buttonType, InputActionType actionType );
	virtual void onMouseMove(const MousePosition& mousePosition);
	virtual void onMouseWheel(const MousePosition& mousePosition, int value);
	

	//virtual void onKeyboard(KEY_TYPE buttonType, INPUT_ACTION_TYPE actionType, unsigned modificators = 0);

	void setVisible(bool visible_);

	static bool RegisterWindowClass(WNDPROC lpfnWndProc, LPCWSTR lpszClassName);
	static Window* GetWindow(HWND hWnd);
	static void AddWindow(HWND hWnd, Window*);
	static void RemoveWindow(HWND hWnd);	
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	
public:

	Window() {}
	~Window() {
		int i = 0;
	}

	HWND getHWND() const { return hWnd; }

	void create(const WindowInfo&);
	void create();
	void destroy();
	void show();
	void hide();
	void update();
	void move(int x, int y);
	void resize(int x, int y);
	//ClientWindowSize getClientWindowSize();


	static void SetInstance(HINSTANCE hInstance_) { hInstance = hInstance_; }

	void addListener(WindowListener*);
	void removeListener(WindowListener*);

	static void SetFramework(Framework*);
	static Framework* GetFramework();

};


/*

#include "RenderSystem.hpp"

class RenderWindow : public Window {

	LPCWSTR getClassName() const { return(L"RenderWindow"); }
	SharedPtr<RenderContext> renderContext;

	void onPaint();
	void onResize(const WindowSize&);
	Framework*  framework;

public:

	RenderWindow() : renderContext(nullptr), framework(nullptr) {}
	~RenderWindow() {
		int i = 0;
	}

	void _setFramework(Framework* framework_) { framework = framework_; }
	
	void setRenderContext(RenderContext* renderContext_);
	RenderContext* getRenderContext() const { return renderContext; }
	//void onPaint() {}

	virtual LPCWSTR getWindowName() const { return(L"RenderWindow"); };
};

*/

class MainWindow : public Window {

	LPCWSTR getClassName() const { return(L"MainWindow"); }

public:

	MainWindow() {}
	//void onPaint() {}

};




}