#pragma once

#include <Windows.h>

#define NUM_KEYS 256

namespace input
{
	/*typedef enum KEY_STATE {
		KEY_UP = 0,
		KEY_DOWN = 1,
		KEY_PRESSED = 2,
		KEY_RELEASED = 3,
	} KEY_STATE;*/


	void Update();
	bool GetKeyDown(int key);
	bool GetKeyPressed(int key);
	bool GetKeyReleased(int key);

	static bool currentState[NUM_KEYS];
	static bool lastState[NUM_KEYS];
}

