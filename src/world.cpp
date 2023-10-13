// world.cpp, holds the state of the level and all its entities
#include "world.hpp"

#include "libtcod.hpp"

Const_Tile::Const_Tile(TCOD_ConsoleTile tile) {
	Const_Tile::tile = tile;
}

Const_Tile::Const_Tile(int ch, TCOD_ColorRGB fg, TCOD_ColorRGB bg) {
	TCOD_ConsoleTile tile{};
	tile.ch = ch;
	tile.fg = fg;
	tile.bg = bg;
	Const_Tile::tile = tile;
}

TCOD_ConsoleTile Const_Tile::get_tile() {
	return Const_Tile::tile;
}

Level::Level(int width, int height) {
	Level::width = width;
	Level::height = height;
	for (int i = 0; i < width * height; ++i) {
		Level::tiles.push_back(new Const_Tile('.', TCOD_ColorRGB{ 127, 127, 127 }, TCOD_ColorRGB{ 0, 0, 0 }));
	}
}

Tile* Level::get_tile(int x, int y) {
	if (x < width && y < height && x >= 0 && y >= 0) {
		return Level::tiles[y * Level::width + x];
	}

	return 0;
}

int Level::get_width() {
	return Level::width;
}

int Level::get_height() {
	return Level::height;
}