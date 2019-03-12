#include "InputModule.hpp"
#include "Framework.hpp"
#include <Windows.h>

namespace Verge3D {

bool InputModule::init(Framework* framework_) {

	Module::init(framework_);
	
	getFramework()->getLogger()->info(L"InputModule initialized...");
	
	return true; 

}

void InputModule::shutdown() {

}

void InputModule::update(float td) {

	KeyState currentKeyState;

	BOOL b = GetKeyboardState(currentKeyState);

	if (b) {

		int i = 0;
		for (uint32_t i = 0; i < 256; i++) {

			if (currentKeyState[i] != prevKeyState[i]) {
				//DebugLog("key index %u value %u", i, currentKeyState[i]);
			}

			prevKeyState[i] = currentKeyState[i];
		}
	}

}

void InputModule::reset() {

	std::memset(&prevKeyState, 0, sizeof(KeyState));

}

void InputModule::addListener(InputListener* listener) {

	listeners.add(listener);

}

void InputModule::removeListener(InputListener* listener) {

	listeners.remove(listener);

}

void InputModule::processKeyboardEvent(const KeyboardEvent& ke) {

	for (size_t i = 0; i < listeners.size(); i++) {
		listeners[i]->onKeyboardAction(ke);
	}
}


}