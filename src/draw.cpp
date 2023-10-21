// draw.cpp, contains utility functions to draw to the TCOD console
#include "draw.hpp"

#include "libtcod.hpp"

inline std::optional<TCOD_ColorRGB> color_to_tcod(Color c) {
	if (c.alpha) {
		return TCOD_ColorRGB{ c.r, c.b, c.g };
	}
	
	return std::nullopt;
}

void print_console_tile(tcod::Console& con, Console_Tile tile, int x, int y) {
	tcod::print(con, { x, y }, std::string(1, tile.ch), color_to_tcod(tile.fg), color_to_tcod(tile.bg));
}
