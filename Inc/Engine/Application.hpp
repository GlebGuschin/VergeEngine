#pragma once

#include "Framework.hpp"
#include "InputModule.hpp"
#include <Windows.h>

namespace Verge3D { 

class Framework;


enum ApplicationState {
	APPLICATION_UNINITIALIZED,
	APPLICATION_WORKING,
	APPLICATION_CLOSED
};


class Application : public InputListener {

	SharedPtr<Framework> framework;

	ApplicationState state;

	//Framework* framework;

	void createFramework();
	void destroyFramework();
	int _run();

	void onException();
	
	void pumpMessages();

protected:

	Framework* getFramework();
	
	virtual void onStart() {}
	virtual void onExit() {}
	virtual void onUpdate();
	virtual void onRefresh() {}

	virtual int mainLoop();

	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;
	LPTSTR lpCmdLine;
	int nCmdShow;

public:
	
	Application() {}

	//bool isClosed() const { return state == APPLICATION_CLOSED; }

	int run();
	int run(int argc, char* argv[]);
	int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);


	void onMouseAction(const MouseEvent&) {}
	void onKeyboardAction(const KeyboardEvent&) {}

};

}