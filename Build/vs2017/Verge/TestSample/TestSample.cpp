// TestSample.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TestSample.h"

#include "TestApplication.hpp"



using namespace Verge3D;

TestApplication app;



int APIENTRY wWinMain(HINSTANCE hInstance_, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {

	
	app.run(hInstance_, hPrevInstance, lpCmdLine, nCmdShow);

	return 0;
}
