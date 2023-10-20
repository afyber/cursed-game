// tile.hpp
#ifndef CURSED_TILE_HPP_
#define CURSED_TILE_HPP_
#include <optional>
#include "libtcod.hpp"
#include "world.hpp"

struct Color {
	bool alpha;
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct Console_Tile {
	int unicode;
	Color fg;
	Color bg;
};

class Const_Tile : public Tile {
private:
	bool solid;
	Console_Tile tile;

public:
	Const_Tile(Console_Tile tile, bool solid);

	Const_Tile(int ch, Color fg, Color bg, bool solid);

	void update(Level* level);

	void interact(Living_Entity* ent);

	bool is_solid();
};

class Door_Tile : public Tile {
private:
	bool open;
	Console_Tile open_tile;
	Console_Tile closed_tile;

public:
	Door_Tile(Console_Tile open_tile, Console_Tile closed_tile);

	void update(Level* level);

	void interact(Living_Entity* ent);

	bool is_solid();
};

#endif
