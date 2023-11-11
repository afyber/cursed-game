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

const Color COLOR_WHITE = { 1, 255, 255, 255 };
const Color COLOR_GREY = { 1, 127, 127, 127 };
const Color COLOR_BLACK = { 1, 0, 0, 0 };
const Color COLOR_BLANK = { 0, 0, 0, 0 };

struct Console_Tile {
	char ch;
	Color fg;
	Color bg;
};

Color color_add(Color c1, Color c2);

Color color_subtract(Color c1, Color c2);

Color color_multiply(Color c, double fac);

std::optional<TCOD_ColorRGB> color_to_tcod(Color c);

void print_console_tile(tcod::Console& con, Console_Tile tile, int x, int y);

void full_console_blit(tcod::Console& src, int src_w, int src_h, tcod::Console& dst, int dst_x, int dst_y);

#endif
