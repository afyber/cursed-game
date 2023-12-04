// Player.cpp
#include "player.hpp"

#include "draw.hpp"
#include "entity.hpp"
#include "keyboard.hpp"
#include "message.hpp"
#include "world.hpp"

Player::Player(int x, int y) : Living_Entity(x, y, 1) {}

int Player::move_actions() {
	return 100;
}

int Player::update(Level& level) {
	int actions = 0;

	if (key_pressed(SDL_SCANCODE_LEFT)) {
		if (move(level, x - 1, y)) {
			send_message("Player moved left", COLOR_WHITE);
		}
		actions = move_actions();
	}
	else if (key_pressed(SDL_SCANCODE_RIGHT)) {
		if (move(level, x + 1, y)) {
			send_message("Player moved right", COLOR_WHITE);
		}
		actions = move_actions();
	}
	else if (key_pressed(SDL_SCANCODE_UP)) {
		if (move(level, x, y - 1)) {
			send_message("Player moved up", COLOR_WHITE);
		}
		actions = move_actions();
	}
	else if (key_pressed(SDL_SCANCODE_DOWN)) {
		if (move(level, x, y + 1)) {
			send_message("Player moved down", COLOR_WHITE);
		}
		actions = move_actions();
	}
	else if (key_pressed(SDL_SCANCODE_PERIOD)) {
		move(level, x, y);
		send_message("Player stood still", COLOR_WHITE);
		actions = move_actions();
	}

	return actions;
}

void Player::draw(tcod::Console& con) {
	print_console_tile(con, Console_Tile{ '@', Color{ 1, 160, 10, 10 }, COLOR_BLANK }, x, y);
}
