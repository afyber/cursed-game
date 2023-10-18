// Player.cpp
#include "player.hpp"
#include "keyboard.hpp"
#include "world.hpp"

Player::Player(int x, int y) : Living_Entity(x, y, 1) {}

void Player::update(Level* level) {
	if (key_pressed(SDL_SCANCODE_LEFT)) {
		move(level, x - 1, y);
	}
	else if (key_pressed(SDL_SCANCODE_RIGHT)) {
		move(level, x + 1, y);
	}
	else if (key_pressed(SDL_SCANCODE_UP)) {
		move(level, x, y - 1);
	}
	else if (key_pressed(SDL_SCANCODE_DOWN)) {
		move(level, x, y + 1);
	}
}
