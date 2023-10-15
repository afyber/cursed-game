// world.hpp
#ifndef CURSED_WORLD_HPP_
#define CURSED_WORLD_HPP_
#include <vector>

#include "tile.hpp"

class Level;
class Entity;

class Level {
private:
	int width, height;
	std::vector<Tile*> tiles;
	std::vector<Entity*> entities;
public:
	Level(int width, int height);

	void update();

	void draw(tcod::Console& con);

	bool can_walk(int x, int y);

	std::vector<Entity*> entities_at(int x, int y);

	void add_entity(Entity* entity);

	Tile* get_tile(int x, int y);

	void set_tile(Tile* tile, int x, int y);

	int get_width();

	int get_height();
};

class Entity {
protected:
	int x, y;

public:
	virtual void update(Level* level) = 0;

	virtual void draw(tcod::Console& con) = 0;

	virtual bool is_passable();

	int get_x();

	int get_y();
};

#endif
