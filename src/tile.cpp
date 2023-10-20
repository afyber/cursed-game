// tile.cpp, Holds tile definitions for all tiles
#include "tile.hpp"
#include <optional>
#include "libtcod.hpp"
#include "world.hpp"

Const_Tile::Const_Tile(Console_Tile tile, bool solid) {
	this->solid = solid;
	this->tile = tile;
}

Const_Tile::Const_Tile(int ch, Color fg, Color bg, bool solid) {
	this->solid = solid;
	Console_Tile new_tile{};
	new_tile.unicode = ch;
	new_tile.fg = fg;
	new_tile.bg = bg;
	tile = new_tile;
}

void Const_Tile::update(Level* level) {}

void Const_Tile::interact(Living_Entity* ent) {}

bool Const_Tile::is_solid() {
	return this->solid;
}

Door_Tile::Door_Tile(Console_Tile open_tile, Console_Tile closed_tile) {
	this->open = false;
	this->open_tile = open_tile;
	this->closed_tile = closed_tile;
}

void Door_Tile::update(Level* level) {}

void Door_Tile::interact(Living_Entity* ent) {
	if (!open) {
		open = true;
	}
}

bool Door_Tile::is_solid() {
	return !this->open;
}
