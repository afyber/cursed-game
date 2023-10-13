// world.hpp
#ifndef CURSED_WORLD_HPP_
#define CURSED_WORLD_HPP_
#include <vector>

#include "tile.hpp"

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
