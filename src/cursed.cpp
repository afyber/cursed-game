// cursed.cpp, entry point for the game
#include <iostream>
#include <string>
#include <SDL.h>

#include "libtcod.hpp"

int main(int argc, char* argv[]) {
	auto params = TCOD_ContextParams();
	params.tcod_version = TCOD_COMPILEDVERSION;
	params.renderer_type = TCOD_RENDERER_SDL2;
	params.vsync = 1;
	params.window_title = "Hello lol";

	tcod::Console con = tcod::Console(30, 20);
	params.console = con.get();

	tcod::ContextPtr context = tcod::new_context(params);

	bool running = true;
	std::string test = "";
	while (running) {

		con.clear();

		tcod::print(con, { 0, 0 }, "A", TCOD_red, TCOD_white);
		tcod::print(con, { 2, 3 }, "Hello world!", TCOD_red, std::nullopt);
		tcod::print(con, { 29, 19 }, "G", TCOD_white, TCOD_blue);
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
					test = "";
				}
			}
		}
	}

	return 0;
}