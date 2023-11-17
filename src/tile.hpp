// tile.hpp
#ifndef CURSED_TILE_HPP_
#define CURSED_TILE_HPP_
#include "libtcod.hpp"
#include <optional>

#include "draw.hpp"
#include "world.hpp"

class Tile : public Object {
public:
	virtual void update(Level& level) = 0;

	virtual Console_Tile get_tile() = 0;
};

class Const_Tile : public Tile {
private:
	Console_Tile tile;
	bool solid, transparent;

public:
	Const_Tile(Console_Tile tile, bool solid, bool transparent);

	Const_Tile(char ch, Color fg, Color bg, bool solid, bool transparent);

	void interact(Living_Entity*);

	bool is_solid();

	bool is_transparent();

	void update(Level&);

	Console_Tile get_tile();
};

class Door_Tile : public Tile {
private:
	Console_Tile open_tile;
	Console_Tile closed_tile;
	bool open;

public:
	Door_Tile(Console_Tile open_tile, Console_Tile closed_tile);

	void interact(Living_Entity*);

	bool is_solid();

	bool is_transparent();

	void update(Level&);

	Console_Tile get_tile();
};

#endif
