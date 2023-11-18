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
		if (move(level, x - 1, y)) {
			send_message("Player moved left", COLOR_WHITE);
		}
		took_turn = true;
	}
	else if (key_pressed(SDL_SCANCODE_RIGHT)) {
		if (move(level, x + 1, y)) {
			send_message("Player moved right", COLOR_WHITE);
		}
		took_turn = true;
	}
	else if (key_pressed(SDL_SCANCODE_UP)) {
		if (move(level, x, y - 1)) {
			send_message("Player moved up", COLOR_WHITE);
		}
		took_turn = true;
	}
	else if (key_pressed(SDL_SCANCODE_DOWN)) {
		if (move(level, x, y + 1)) {
			send_message("Player moved down", COLOR_WHITE);
		}
		took_turn = true;
	}
	else if (key_pressed(SDL_SCANCODE_PERIOD)) {
		move(level, x, y);
		send_message("Player stood still.\nBut why though?", COLOR_WHITE);
		took_turn = true;
	}

	return took_turn;
}

void Player::draw(tcod::Console& con) {
	print_console_tile(con, Console_Tile{ '@', COLOR_WHITE, COLOR_BLANK }, x, y);
}
