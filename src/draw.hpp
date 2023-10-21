// draw.hpp
#ifndef CURSED_DRAW_HPP_
#define CURSED_DRAW_HPP_
#include "libtcod.hpp"

struct Color {
	bool alpha;
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct Console_Tile {
	char ch;
	Color fg;
	Color bg;
};

inline std::optional<TCOD_ColorRGB> color_to_tcod(Color c);

void print_console_tile(tcod::Console& con, Console_Tile tile, int x, int y);

#endif
