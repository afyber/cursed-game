// map.hpp
#ifndef CURSED_MAP_HPP_
#define CURSED_MAP_HPP_
#include "libtcod.hpp"

class Living_Entity;
class Level;
class Tile;

struct Map_Tile {
	Tile* tile_ref;
	bool visible, seen;
};

class Map {
private:
	int width, height;
	std::vector<Map_Tile> tiles;

public:
	Map(int width, int height);

	void update(Level& level);

	void draw(tcod::Console& con);

	void interact(int x, int y, Living_Entity* ent);

	bool is_solid(int x, int y);

	bool is_transparent(int x, int y);

	bool is_visible(int x, int y);

	bool seen(int x, int y);
};

#endif
