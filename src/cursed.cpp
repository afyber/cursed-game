// cursed.cpp, entry point for the game
#include <array>
#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL2/SDL_image.h>

#include "libtcod.hpp"

const int TILESET_CHAR_SIZE = 8;
const int TILESET_CHARS = 16;
const int CONSOLE_WIDTH = 20;
const int CONSOLE_HEIGHT = 30;

int main(int argc, char* argv[]) {
	auto params = TCOD_ContextParams();
	params.tcod_version = TCOD_COMPILEDVERSION;
	params.renderer_type = TCOD_RENDERER_SDL2;
	params.vsync = 1;
	params.window_title = "Cursed";

	tcod::Tileset tileset = tcod::load_tilesheet<>("data/tileset.png", { TILESET_CHARS, TILESET_CHARS }, tcod::CHARMAP_CP437);
	params.tileset = tileset.get();

	tcod::Console con = tcod::Console(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	params.console = con.get();

	tcod::ContextPtr context = tcod::new_context(params);

	int scale_multiplier = 2;
	SDL_SetWindowSize(context->get_sdl_window(), TILESET_CHAR_SIZE * CONSOLE_WIDTH * scale_multiplier, TILESET_CHAR_SIZE * CONSOLE_HEIGHT * scale_multiplier);

	bool running = true;
	std::string test = "";
	while (running) {

		con.clear();

		tcod::print(con, { 0, 0 }, "A", TCOD_red, TCOD_white);
		tcod::print(con, { 2, 3 }, "Hello world!", TCOD_red, std::nullopt);
		tcod::print(con, { 19, 29 }, "G", TCOD_white, TCOD_blue);
		tcod::print(con, { 2, 4 }, test, TCOD_white, std::nullopt);

		context->present(con);

		SDL_Event event;
		while (SDL_PollEvent(&event) != NULL) {
			// we have an event to handle
			if (event.type == SDL_QUIT) {
				running = false;
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym < 256 && std::isalnum(event.key.keysym.sym)) {
					test += (char)event.key.keysym.sym;
				}
				if (event.key.keysym.sym == SDLK_RETURN) {
					if (test == "inc") {
						scale_multiplier++;
						SDL_SetWindowSize(context->get_sdl_window(), TILESET_CHAR_SIZE * CONSOLE_WIDTH * scale_multiplier, TILESET_CHAR_SIZE * CONSOLE_HEIGHT * scale_multiplier);
					}
					else if (test == "dec") {
						scale_multiplier--;
						SDL_SetWindowSize(context->get_sdl_window(), TILESET_CHAR_SIZE * CONSOLE_WIDTH * scale_multiplier, TILESET_CHAR_SIZE * CONSOLE_HEIGHT * scale_multiplier);
					}
					test = "";
				}
			}
		}
	}

	return 0;
}