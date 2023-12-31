// keyboard.hpp
#ifndef CURSED_KEYBOARD_HPP_
#define CURSED_KEYBOARD_HPP_
#include <SDL.h>

bool key_down(SDL_Scancode scancode);

/**
 * @returns true if the key was pressed since the last update, false otherwise
 */
bool key_pressed(SDL_Scancode scancode);

/**
 * @returns true if the key was typed since the last update, which will happen multiple times as a key is held down, false otherwise
 */
bool key_typed(SDL_Scancode scancode);

/**
 * @returns true if the key was released since the last update, false otherwise
 */
bool key_released(SDL_Scancode scancode);

bool key_enter_pressed();

void update_key_states();

void handle_key_event(SDL_KeyboardEvent event);

#endif
