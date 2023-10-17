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
		tile->interact(this);
	}
}

Player::Player(int x, int y) {
	this->x = x;
	this->y = y;
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

bool Player::is_solid() {
	return true;
}

void Player::hurt(Cursed_Attack attack) {
	health -= attack.normal_damage + attack.magic_damage + attack.fire_damage;
}

bool Player::is_alive() {
	return health > 0;
}