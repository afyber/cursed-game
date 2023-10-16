// tile.hpp
#ifndef CURSED_TILE_HPP_
#define CURSED_TILE_HPP_
#include <optional>
#include "libtcod.hpp"
#include "world.hpp"

class Const_Tile : public Tile {
private:
	bool passable;
	TCOD_ConsoleTile tile;

public:
	Const_Tile(TCOD_ConsoleTile tile, bool passable);

	Const_Tile(int ch, TCOD_ColorRGB fg, std::optional<TCOD_ColorRGB> bg, bool passable);

	bool is_passable();

	void interact();

	TCOD_ConsoleTile get_tile();
};

class Door_Tile : public Tile {
private:
	bool open;
	TCOD_ConsoleTile open_tile;
	TCOD_ConsoleTile closed_tile;

public:
	Door_Tile(TCOD_ConsoleTile open_tile, TCOD_ConsoleTile closed_tile);

	bool is_passable();

	void interact();

	TCOD_ConsoleTile get_tile();
};

#endif
