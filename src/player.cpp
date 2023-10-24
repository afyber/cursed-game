// Player.cpp
#include "player.hpp"

#include "draw.hpp"
#include "entity.hpp"
#include "keyboard.hpp"
#include "message.hpp"
#include "world.hpp"

Player::Player(int x, int y) : Living_Entity(x, y, 1) {}

bool Player::update(Level& level) {
	bool took_turn = false;

	if (key_pressed(SDL_SCANCODE_LEFT)) {
		move(level, x - 1, y);
		took_turn = true;

		send_message("Player moved left", COLOR_WHITE);
	}
	else if (key_pressed(SDL_SCANCODE_RIGHT)) {
		move(level, x + 1, y);
		took_turn = true;

		send_message("Player moved right", COLOR_WHITE);
	}
	else if (key_pressed(SDL_SCANCODE_UP)) {
		move(level, x, y - 1);
		took_turn = true;

		send_message("Player moved up", COLOR_WHITE);
	}
	else if (key_pressed(SDL_SCANCODE_DOWN)) {
		move(level, x, y + 1);
		took_turn = true;

		send_message("Player moved down", COLOR_WHITE);
	}
	else if (key_pressed(SDL_SCANCODE_PERIOD)) {
		move(level, x, y);
		took_turn = true;

		send_message("Player stood still, lol why are you standing still dummy, are you lost? What on earth could you possibly want to do.", COLOR_WHITE);
	}

	return took_turn;
}

void Player::draw(tcod::Console& con) {
	print_console_tile(con, { '@', COLOR_WHITE, COLOR_BLANK }, x, y);
}
