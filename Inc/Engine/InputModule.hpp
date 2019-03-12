#pragma once

#include "Module.hpp"
#include "Input.hpp"
#include "DynamicArray.hpp"

namespace Verge3D {

class InputModule : public Module {

	typedef BYTE KeyState[256];
	KeyState prevKeyState;

	void reset();

	DynamicArray<InputListener*> listeners;
	
public:

	InputModule() : Module("InputModule") {}

	bool init(Framework* framework_);

	void shutdown();
	void update(float td);

	void addListener(InputListener*);
	void removeListener(InputListener*);

	void processKeyboardEvent(const KeyboardEvent&);

};

}