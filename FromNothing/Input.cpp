#include "Input.h"

void input::Update()
{
	for (int i = 0; i < NUM_KEYS; i++) {
		lastState[i] = currentState[i];
		currentState[i] = GetAsyncKeyState(i);
	}
}

bool input::GetKeyDown(int key)
{
	return currentState[key];
}

bool input::GetKeyPressed(int key)
{
	return currentState[key] && !lastState[key];
}

bool input::GetKeyReleased(int key)
{
	return !currentState[key] && lastState[key];
}
