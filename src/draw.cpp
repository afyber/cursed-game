// draw.cpp, contains utility functions to draw to the TCOD console
#include "draw.hpp"

#include "libtcod.hpp"

inline std::optional<TCOD_ColorRGB> color_to_tcod(Color c) {
	return c.alpha ? std::optional(TCOD_ColorRGB{ c.r, c.g, c.b }) : std::nullopt;
}

void print_console_tile(tcod::Console& con, Console_Tile tile, int x, int y) {
	tcod::print(con, { x, y }, std::string(1, tile.ch), color_to_tcod(tile.fg), color_to_tcod(tile.bg));
}

void full_console_blit(tcod::Console& src, int src_w, int src_h, tcod::Console& dst, int dst_x, int dst_y) {
	TCOD_console_blit(src.get(), 0, 0, src_w, src_h, dst.get(), dst_x, dst_y, 1, 1);
}