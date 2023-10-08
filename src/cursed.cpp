// cursed.cpp, entry point for the game
#include <iostream>
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

	con.clear();

	tcod::print(con, { 2, 3 }, "Hello world!", TCOD_white, std::nullopt);

	context->present(con);

	bool running = true;
	while (running) {

		SDL_Event event;
		while (SDL_PollEvent(&event) != NULL) {
			// we have an event to handle
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}
	}

	return 0;
}