// Player.cpp
#include "player.hpp"
#include "keyboard.hpp"
#include "world.hpp"

void Player::move(Level* level, int x, int y) {
	if (level->can_walk(x, y)) {
		this->x = x;
		this->y = y;
	}

	Tile* tile = level->get_tile(x, y);
	if (tile) {
		tile->interact();
	}
}

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

void Player::draw(tcod::Console& con) {
	con.at({ x, y }).ch = (int)'@';
	con.at({ x, y }).fg = TCOD_ColorRGB{ 255, 255, 255 };
}