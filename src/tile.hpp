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

	virtual void draw(tcod::Console& con, int x, int y) = 0;
};

class Const_Tile : public Tile {
private:
	bool solid, transparent;
	Console_Tile tile;

public:
	Const_Tile(Console_Tile tile, bool solid, bool transparent);

	Const_Tile(char ch, Color fg, Color bg, bool solid, bool transparent);

	void interact(Living_Entity*);

	bool is_solid();

	bool is_transparent();

	void update(Level&);

	void draw(tcod::Console& con, int x, int y);
};

class Door_Tile : public Tile {
private:
	bool open;
	Console_Tile open_tile;
	Console_Tile closed_tile;

public:
	Door_Tile(Console_Tile open_tile, Console_Tile closed_tile);

	void interact(Living_Entity*);

	bool is_solid();

	bool is_transparent();

	void update(Level&);

	void draw(tcod::Console& con, int x, int y);
};

#endif
