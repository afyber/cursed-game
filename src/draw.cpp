// draw.cpp, contains utility functions to draw to the TCOD console
#include "draw.hpp"

#include "libtcod.hpp"

Color color_add(Color c1, Color c2) {
	return Color{ c1.alpha && c2.alpha, (uint8_t)std::clamp(c1.r + c2.r, 0, 255), (uint8_t)std::clamp(c1.g + c2.g, 0, 255), (uint8_t)std::clamp(c1.b + c2.b, 0, 255) };
}

Color color_subtract(Color c1, Color c2) {
	return Color{ c1.alpha && c2.alpha, (uint8_t)std::clamp(c1.r - c2.r, 0, 255), (uint8_t)std::clamp(c1.g - c2.g, 0, 255), (uint8_t)std::clamp(c1.b - c2.b, 0, 255) };
}

Color color_multiply(Color c, double fac) {
	return Color{ c.alpha, (uint8_t)std::clamp(c.r * fac, 0.0, 255.0), (uint8_t)std::clamp(c.g * fac, 0.0, 255.0), (uint8_t)std::clamp(c.b * fac, 0.0, 255.0) };
}

std::optional<TCOD_ColorRGB> color_to_tcod(Color c) {
	return c.alpha ? std::optional(TCOD_ColorRGB{ c.r, c.g, c.b }) : std::nullopt;
}

void print_console_tile(tcod::Console& con, Console_Tile tile, int x, int y) {
	tcod::print(con, { x, y }, std::string(1, tile.ch), color_to_tcod(tile.fg), color_to_tcod(tile.bg));
}

void full_console_blit(tcod::Console& src, int src_w, int src_h, tcod::Console& dst, int dst_x, int dst_y) {
	TCOD_console_blit(src.get(), 0, 0, src_w, src_h, dst.get(), dst_x, dst_y, 1, 1);
}