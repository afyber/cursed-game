// cursed.cpp, entry point for the game
#include <array>
#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL2/SDL_image.h>

#include "libtcod.hpp"

#include "keyboard.hpp"

const int TILESET_CHAR_SIZE = 8;
const int TILESET_COLUMNS = 16;
const int TILESET_ROWS = 16;
const int CONSOLE_WIDTH = 20;
const int CONSOLE_HEIGHT = 30;

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

	int scale_multiplier = 2;
	SDL_SetWindowSize(context.get_sdl_window(), TILESET_CHAR_SIZE * CONSOLE_WIDTH * scale_multiplier, TILESET_CHAR_SIZE * CONSOLE_HEIGHT * scale_multiplier);

	bool running = true;
	std::string test = "";
	int code = 0;
	int x = 0;
	int y = 0;
	while (running) {

		if (key_pressed(SDL_SCANCODE_RIGHT)) {
			x++;
		}
		if (key_pressed(SDL_SCANCODE_LEFT)) {
			x--;
		}
		if (key_pressed(SDL_SCANCODE_UP)) {
			y--;
		}
		if (key_pressed(SDL_SCANCODE_DOWN)) {
			y++;
		}

		con.clear();

		tcod::print(con, { x, y }, "A", TCOD_ColorRGB{ 255, 0, 0 }, TCOD_ColorRGB{ 255, 255, 255 });
		tcod::print(con, { 2, 3 }, "Hello world!", TCOD_ColorRGB{ 255, 0, 0 }, std::nullopt);
		tcod::print(con, { 19, 29 }, "G", TCOD_ColorRGB{ 255, 255, 255 }, TCOD_ColorRGB{ 0, 0, 255 });
		tcod::print(con, { 2, 4 }, test, TCOD_ColorRGB{ 255, 255, 255 }, std::nullopt);
		tcod::print(con, { 2, 5 }, std::to_string(code), TCOD_ColorRGB{ 255, 255, 255 }, std::nullopt);

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