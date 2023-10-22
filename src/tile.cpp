// tile.cpp, Holds tile definitions for all tiles
#include "tile.hpp"

#include "libtcod.hpp"
#include <optional>

#include "draw.hpp"
#include "world.hpp"

// class Const_Tile

Const_Tile::Const_Tile(Console_Tile tile, bool solid) {
	this->solid = solid;
	this->tile = tile;
}

Const_Tile::Const_Tile(char ch, Color fg, Color bg, bool solid) {
	this->solid = solid;
	tile = { ch, fg, bg };
}

void Const_Tile::update(Level& level) {}

void Const_Tile::draw(tcod::Console& con, int x, int y) {
	print_console_tile(con, tile, x, y);
}

void Const_Tile::interact(Living_Entity* ent) {}

bool Const_Tile::is_solid() {
	return this->solid;
}

// class Door_Tile

Door_Tile::Door_Tile(Console_Tile open_tile, Console_Tile closed_tile) {
	this->open = false;
	this->open_tile = open_tile;
	this->closed_tile = closed_tile;
}

void Door_Tile::update(Level& level) {}

void Door_Tile::draw(tcod::Console& con, int x, int y) {
	if (open) {
		print_console_tile(con, open_tile, x, y);
	}
	else {
		print_console_tile(con, closed_tile, x, y);
	}
}

void Door_Tile::interact(Living_Entity* ent) {
	if (!open) {
		open = true;
	}
}

bool Door_Tile::is_solid() {
	return !this->open;
}
