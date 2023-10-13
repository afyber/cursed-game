// tile.cpp, Holds tile definitions for all tiles
#include "tile.hpp"
#include <optional>
#include "libtcod.hpp"

Const_Tile::Const_Tile(TCOD_ConsoleTile tile, bool passable) {
	Const_Tile::passable = passable;
	Const_Tile::tile = tile;
}

Const_Tile::Const_Tile(int ch, TCOD_ColorRGB fg, std::optional<TCOD_ColorRGB> bg, bool passable) {
	Const_Tile::passable = passable;
	TCOD_ConsoleTile tile{};
	tile.ch = ch;
	tile.fg = fg;
	if (bg) {
		tile.bg = bg.value();
	}
	else {
		tile.bg = TCOD_ColorRGBA{};
	}
	Const_Tile::tile = tile;
}

bool Const_Tile::is_passable() {
	return Const_Tile::passable;
}

void Const_Tile::interact() {}

TCOD_ConsoleTile Const_Tile::get_tile() {
	return Const_Tile::tile;
}

Door_Tile::Door_Tile(TCOD_ConsoleTile open_tile, TCOD_ConsoleTile closed_tile) {
	Door_Tile::open = false;
	Door_Tile::open_tile = open_tile;
	Door_Tile::closed_tile = closed_tile;
}

bool Door_Tile::is_passable() {
	return Door_Tile::open;
}

void Door_Tile::interact() {
	if (!open) {
		open = true;
	}
}

TCOD_ConsoleTile Door_Tile::get_tile() {
	if (open) {
		return Door_Tile::open_tile;
	}
	else {
		return Door_Tile::closed_tile;
	}
}