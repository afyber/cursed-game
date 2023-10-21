// keyboard.cpp, handles SDL_KeyboardEvent's and stores the state of the keys
#include "keyboard.hpp"

#include <SDL.h>

/* The possible states of a key. All values greater than zero indicate the key is being held down, all values less than or equal to zero indicate it is not.
 * JUST_RELEASED: The key was released since the last update
 * KEY_UP: The key is not being held down
 * JUST_PRESSED: The key has been pressed since the last update
 * RE_TYPED: The key has been typed again, but is still being held down (because holding down a key types it again repeatedly)
 * KEY_DOWN: The key is being held down
 */
enum KEY_STATE {
	JUST_RELEASED = -1,
	KEY_UP = 0,
	JUST_PRESSED = 1,
	RE_TYPED = 2,
	KEY_DOWN = 3
};

KEY_STATE KEYS[SDL_NUM_SCANCODES] = { KEY_UP };

bool key_down(SDL_Scancode scancode) {
	return KEYS[scancode] > 0;
}

bool key_pressed(SDL_Scancode scancode) {
	return KEYS[scancode] == JUST_PRESSED;
}

bool key_typed(SDL_Scancode scancode) {
	return KEYS[scancode] == JUST_PRESSED || KEYS[scancode] == RE_TYPED;
}

bool key_released(SDL_Scancode scancode) {
	return KEYS[scancode] == JUST_RELEASED;
}

void update_key_states() {
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		if (KEYS[i] == JUST_PRESSED || KEYS[i] == RE_TYPED) {
			KEYS[i] = KEY_DOWN;
		}
		else if (KEYS[i] == JUST_RELEASED) {
			KEYS[i] = KEY_UP;
		}
	}
}

void handle_key_event(SDL_KeyboardEvent event) {
	if (event.type == SDL_KEYDOWN) {
		if (KEYS[event.keysym.scancode] <= 0) {
			KEYS[event.keysym.scancode] = JUST_PRESSED;
		}
		else {
			KEYS[event.keysym.scancode] = RE_TYPED;
		}
	}
	else if (event.type == SDL_KEYUP) {
		KEYS[event.keysym.scancode] = JUST_RELEASED;
	}
}
