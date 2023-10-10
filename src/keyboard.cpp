// keyboard.cpp, handles SDL_KeyboardEvent's and stores the state of the keys
#include "keyboard.hpp"
#include <SDL.h>

enum KEY_STATE {
	JUST_RELEASED = -1,
	NOT_DOWN = 0,
	JUST_PRESSED = 1,
	RE_TYPED = 2,
	KEY_DOWN = 3
};

/* Holds the state of every key on the keyboard as a number. All values greater than zero indicate the key is being held down, all values less than or equal to zero indicate it is not.
 * -1: The key was released since the last call to update_key_states()
 * 0: The key is not being held down
 * 1: Has been typed for the first time after not being held down
 * 2: The key has been typed again, but is still being held down
 * 3: They key is being held down
 */
int8_t KEY_STATES[SDL_NUM_SCANCODES] = { 0 };

bool key_down(SDL_Keycode key_scancode) {
	return KEY_STATES[key_scancode] > 0;
}

bool key_pressed(SDL_Keycode key_scancode) {
	return KEY_STATES[key_scancode] == JUST_PRESSED;
}

bool key_typed(SDL_Keycode key_scancode) {
	return KEY_STATES[key_scancode] == JUST_PRESSED || KEY_STATES[key_scancode] == RE_TYPED;
}

bool key_released(SDL_Keycode key_scancode) {
	return KEY_STATES[key_scancode] == JUST_RELEASED;
}

void update_key_states() {
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		if (KEY_STATES[i] == JUST_PRESSED || KEY_STATES[i] == RE_TYPED) {
			KEY_STATES[i] = KEY_DOWN;
		}
		else if (KEY_STATES[i] == JUST_RELEASED) {
			KEY_STATES[i] = NOT_DOWN;
		}
	}
}

void handle_key_event(SDL_KeyboardEvent event) {
	if (event.type == SDL_KEYDOWN) {
		if (KEY_STATES[event.keysym.scancode] <= 0) {
			KEY_STATES[event.keysym.scancode] = JUST_PRESSED;
		}
		else {
			KEY_STATES[event.keysym.scancode] = RE_TYPED;
		}
	}
	else if (event.type == SDL_KEYUP) {
		KEY_STATES[event.keysym.scancode] = JUST_RELEASED;
	}
}