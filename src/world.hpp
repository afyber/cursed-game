// world.hpp
#ifndef CURSED_WORLD_HPP_
#define CURSED_WORLD_HPP_
#include "libtcod.hpp"
#include <vector>

class Entity;
class Living_Entity;
class Player;
class Tile;

class Object {
public:
	virtual void interact(Living_Entity* ent) = 0;

	virtual bool is_solid() = 0;

	virtual bool is_transparent() = 0;
};

class Level {
private:
	int width, height;
	std::vector<Tile*> tiles;
	std::vector<Entity*> entities;

	Player* player;

	TCODMap visibility_map;

	void calculate_visibility(int origin_x, int origin_y);
public:
	Level(int width, int height, Player* player);

	void update();

	void draw(tcod::Console& con);

	bool can_walk(int x, int y);

	std::vector<Entity*> entities_at(int x, int y);

	void add_entity(Entity* entity);

	bool remove_entity(Entity* entity);

	Tile* get_tile(int x, int y);

	void set_tile(Tile* tile, int x, int y);

	int get_width();

	int get_height();
};

#endif
