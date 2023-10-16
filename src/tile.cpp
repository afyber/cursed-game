// tile.cpp, Holds tile definitions for all tiles
#include "tile.hpp"
#include <optional>
#include "libtcod.hpp"
#include "world.hpp"

Const_Tile::Const_Tile(TCOD_ConsoleTile tile, bool solid) {
	this->solid = solid;
	this->tile = tile;
}

Const_Tile::Const_Tile(int ch, TCOD_ColorRGB fg, std::optional<TCOD_ColorRGB> bg, bool solid) {
	this->solid = solid;
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

void Const_Tile::update(Level* level) {}

bool Const_Tile::is_solid() {
	return this->solid;
}

void Const_Tile::interact(Entity* ent) {}

Door_Tile::Door_Tile(TCOD_ConsoleTile open_tile, TCOD_ConsoleTile closed_tile) {
	Door_Tile::open = false;
	Door_Tile::open_tile = open_tile;
	Door_Tile::closed_tile = closed_tile;
}

void Door_Tile::update(Level* level) {}

bool Door_Tile::is_solid() {
	return this->open;
}

void Door_Tile::interact(Entity* ent) {
	if (!open) {
		open = true;
	}
}
