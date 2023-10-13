// world.hpp
#ifndef CURSED_WORLD_HPP_
#define CURSED_WORLD_HPP_
#include <vector>
#include "libtcod.hpp"

class Tile {
public:
	virtual TCOD_ConsoleTile get_tile() = 0;
};

class Const_Tile : public Tile {
private:
	TCOD_ConsoleTile tile;

public:
	Const_Tile(TCOD_ConsoleTile);

	Const_Tile(int ch, TCOD_ColorRGB fg, TCOD_ColorRGB bg);

	TCOD_ConsoleTile get_tile();
};

class Level {
private:
	int width;
	int height;
	std::vector<Tile*> tiles;
public:
	Level(int width, int height);

	Tile* get_tile(int x, int y);

	int get_width();

	int get_height();
};

#endif
