// cursed.cpp, entry point for the game
#include <array>
#include <iostream>
#include "libtcod.hpp"
#include "libtcod/timer.hpp"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "draw.hpp"
#include "keyboard.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "player.hpp"
#include "random.hpp"
#include "world.hpp"

const int WINDOW_DESIRED_FPS = 60;

const int CONSOLE_WIDTH = 80;
const int CONSOLE_HEIGHT = 45;

const int TILESET_CHAR_SIZE = 8;
const int TILESET_COLUMNS = 16;
const int TILESET_ROWS = 16;

const int LEVEL_X = 0;
const int LEVEL_Y = 0;
const int LEVEL_WIDTH = 45;
const int LEVEL_HEIGHT = 45;

const int MESSAGE_BOX_X = 45;
const int MESSAGE_BOX_Y = 0;
const int MESSAGE_BOX_WIDTH = 35;
const int MESSAGE_BOX_HEIGHT = 45;

void setup_tcod(tcod::Console& console_out, tcod::Context& context_out) {
	auto params = TCOD_ContextParams();
	params.tcod_version = TCOD_COMPILEDVERSION;
	params.renderer_type = TCOD_RENDERER_SDL2;
	params.vsync = 1;
	params.window_title = "Cursed";

	tcod::Tileset tileset = tcod::load_tilesheet("data/tileset.png", { TILESET_COLUMNS, TILESET_ROWS }, tcod::CHARMAP_CP437);
	params.tileset = tileset.get();

	console_out = tcod::Console(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	params.console = console_out.get();

	context_out = tcod::Context(params);
}

void sdl_set_window_size(tcod::Context& context, int multiplier) {
	SDL_SetWindowSize(context.get_sdl_window(), TILESET_CHAR_SIZE * CONSOLE_WIDTH * multiplier, TILESET_CHAR_SIZE * CONSOLE_HEIGHT * multiplier);
	SDL_SetWindowPosition(context.get_sdl_window(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void sdl_set_initial_window_size(tcod::Context& context) {
	SDL_DisplayMode mode;
	if (SDL_GetDesktopDisplayMode(0, &mode) != 0) {
		sdl_set_window_size(context, 1);
	}
	else {
		// set the scaling multiplier to the largest integer which makes the window smaller than the screen, and also never allows a multiplier of < 1
		sdl_set_window_size(context, std::max(1, (int)std::ceil(mode.w / (TILESET_CHAR_SIZE * CONSOLE_WIDTH)) - 1));
	}
}

int setup_sdl(tcod::Context& context) {
	if ((IMG_Init(IMG_InitFlags::IMG_INIT_PNG) & IMG_INIT_PNG) == 0) {
		return -1;
	}

	SDL_SetWindowIcon(context.get_sdl_window(), IMG_Load("data/icon.png"));

	sdl_set_initial_window_size(context);

	return 0;
}

void quit_sdl() {
	IMG_Quit();
}

int main(int argc, char* argv[]) {
	// TODO: parse these
	(void)argc;
	(void)argv;

	setup_random();

	tcod::Console con;
	tcod::Context context;
	setup_tcod(con, context);

	if (setup_sdl(context) != 0) {
		return -1;
	}

	tcod::Console message_con = tcod::Console(MESSAGE_BOX_WIDTH, MESSAGE_BOX_HEIGHT);
	tcod::Console level_con = tcod::Console(LEVEL_WIDTH, LEVEL_HEIGHT);

	Player* player = new Player(5, 5);
	Level floor(LEVEL_WIDTH, LEVEL_HEIGHT, player);
	floor.add_entity(new Item_Entity(5, 4, new Item(0)));
	floor.add_entity(new Goblin_Entity(10, 10));

	menu_push(new Choice_Menu("Will you yeild?"));

	auto timer = tcod::Timer();

	bool running = true;
	while (running) {
		if (!menu_open()) {
			floor.update();
			update_messages();
		}

		update_menus();

		con.clear();

		level_con.clear();
		floor.draw(level_con);
		full_console_blit(level_con, LEVEL_WIDTH, LEVEL_HEIGHT, con, LEVEL_X, LEVEL_Y);

		message_con.clear();
		draw_messages(message_con, MESSAGE_BOX_WIDTH, MESSAGE_BOX_HEIGHT);
		full_console_blit(message_con, MESSAGE_BOX_WIDTH, MESSAGE_BOX_HEIGHT, con, MESSAGE_BOX_X, MESSAGE_BOX_Y);

		draw_menus(con);

		context.present(con);

		update_key_states();

		timer.sync(WINDOW_DESIRED_FPS);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			// we have an event to handle
			switch (event.type) {
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				handle_key_event(event.key);
				break;
			case SDL_QUIT:
				running = false;
			}
		}
	}

	delete player;

	quit_sdl();

	return 0;
}
