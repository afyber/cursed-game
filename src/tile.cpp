// tile.cpp, Holds tile definitions for all tiles
#include "tile.hpp"

#include "libtcod.hpp"
#include <optional>

#include "draw.hpp"
#include "world.hpp"

// class Const_Tile

Const_Tile::Const_Tile(Console_Tile tile, bool solid, bool transparent) {
	this->solid = solid;
	this->tile = tile;
	this->transparent = transparent;
}

Const_Tile::Const_Tile(char ch, Color fg, Color bg, bool solid, bool transparent) {
	this->solid = solid;
	this->transparent = transparent;
	tile = { ch, fg, bg };
}

void Const_Tile::interact(Living_Entity*) {}

bool Const_Tile::is_solid() {
	return solid;
}

bool Const_Tile::is_transparent() {
	return transparent;
}

void Const_Tile::update(Level&) {}

void Const_Tile::draw(tcod::Console& con, int x, int y) {
	print_console_tile(con, tile, x, y);
}

// class Door_Tile

Door_Tile::Door_Tile(Console_Tile open_tile, Console_Tile closed_tile) {
	this->open = false;
	this->open_tile = open_tile;
	this->closed_tile = closed_tile;
}

void Door_Tile::interact(Living_Entity*) {
	if (!open) {
		open = true;
	}
}

bool Door_Tile::is_solid() {
	return !open;
}

bool Door_Tile::is_transparent() {
	return open;
}

void Door_Tile::update(Level&) {}

void Door_Tile::draw(tcod::Console& con, int x, int y) {
	if (open) {
		print_console_tile(con, open_tile, x, y);
	}
	else {
		print_console_tile(con, closed_tile, x, y);
	}
}
