// cursed.cpp, entry point for the game
#include <array>
#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL2/SDL_image.h>

#include "libtcod.hpp"

#include "keyboard.hpp"
#include "world.hpp"
#include "player.hpp"

const int TILESET_CHAR_SIZE = 8;
const int TILESET_COLUMNS = 16;
const int TILESET_ROWS = 16;
const int CONSOLE_WIDTH = 80;
const int CONSOLE_HEIGHT = 45;

void setup_tcod(tcod::Console& console_out, tcod::Context& context_out) {
	auto params = TCOD_ContextParams();
	params.tcod_version = TCOD_COMPILEDVERSION;
	params.renderer_type = TCOD_RENDERER_SDL2;
	params.vsync = 1;
	params.window_title = "Cursed";

	tcod::Tileset tileset = tcod::load_tilesheet<>("data/tileset.png", { TILESET_COLUMNS, TILESET_ROWS }, tcod::CHARMAP_CP437);
	params.tileset = tileset.get();

	console_out = tcod::Console(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	params.console = console_out.get();

	context_out = tcod::Context(params);
}

int setup_sdl(tcod::Context& context) {
	if (IMG_Init(IMG_InitFlags::IMG_INIT_PNG) == 0) {
		return -1;
	}

	SDL_SetWindowIcon(context.get_sdl_window(), IMG_Load("data/icon.png"));
	return 0;
}

void sdl_set_window_size(tcod::Context& context, int multiplier) {
	SDL_SetWindowSize(context.get_sdl_window(), TILESET_CHAR_SIZE * CONSOLE_WIDTH * multiplier, TILESET_CHAR_SIZE * CONSOLE_HEIGHT * multiplier);
}

void quit_sdl() {
	IMG_Quit();
}

int main(int argc, char* argv[]) {
	tcod::Console con;
	tcod::Context context;
	setup_tcod(con, context);

	if (setup_sdl(context) != 0) {
		return -1;
	}

	sdl_set_window_size(context, 2);

	Level floor(45, 45);
	floor.add_entity(new Player(5, 5));

	bool running = true;
	while (running) {
		con.clear();

		floor.update();

		floor.draw(con);

		context.present(con);

		update_key_states();

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

	quit_sdl();

	return 0;
}
