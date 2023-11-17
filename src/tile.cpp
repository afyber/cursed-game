// tile.cpp, Holds tile definitions for all tiles
#include "tile.hpp"

#include "libtcod.hpp"
#include <optional>

#include "draw.hpp"
#include "world.hpp"

// class Const_Tile

Const_Tile::Const_Tile(Console_Tile tile, bool solid, bool transparent) : tile(tile), solid(solid), transparent(transparent) {}

Const_Tile::Const_Tile(char ch, Color fg, Color bg, bool solid, bool transparent) : tile(Console_Tile{ ch, fg, bg }), solid(solid), transparent(transparent) {}

void Const_Tile::interact(Living_Entity*) {}

bool Const_Tile::is_solid() {
	return solid;
}

bool Const_Tile::is_transparent() {
	return transparent;
}

void Const_Tile::update(Level&) {}

Console_Tile Const_Tile::get_tile() {
	return tile;
}

// class Door_Tile

Door_Tile::Door_Tile(Console_Tile open_tile, Console_Tile closed_tile) : open_tile(open_tile), closed_tile(closed_tile), open(false) {}

void Door_Tile::interact(Living_Entity*) {
	open = true;
}

bool Door_Tile::is_solid() {
	return !open;
}

bool Door_Tile::is_transparent() {
	return open;
}

void Door_Tile::update(Level&) {}

Console_Tile Door_Tile::get_tile() {
	return open ? open_tile : closed_tile;
}
