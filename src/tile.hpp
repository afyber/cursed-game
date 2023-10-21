// tile.hpp
#ifndef CURSED_TILE_HPP_
#define CURSED_TILE_HPP_
#include <optional>
#include "draw.hpp"
#include "libtcod.hpp"
#include "world.hpp"

class Const_Tile : public Tile {
private:
	bool solid;
	Console_Tile tile;

public:
	Const_Tile(Console_Tile tile, bool solid);

	Const_Tile(char ch, Color fg, Color bg, bool solid);

	void update(Level* level);

	void draw(tcod::Console& con, int x, int y);

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

	void draw(tcod::Console& con, int x, int y);

	void interact(Living_Entity* ent);

	bool is_solid();
};

#endif
