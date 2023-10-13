// tile.hpp
#ifndef CURSED_TILE_HPP_
#define CURSED_TILE_HPP_
#include <optional>
#include "libtcod.hpp"

class Tile {
public:
	virtual bool is_passable() = 0;

	// TODO: should include a reference to the inventory of the player/creature attempting to interact with it
	virtual void interact() = 0;

	virtual TCOD_ConsoleTile get_tile() = 0;
};

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
