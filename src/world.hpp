// world.hpp
#ifndef CURSED_WORLD_HPP_
#define CURSED_WORLD_HPP_
#include <vector>
#include "libtcod.hpp"

class Object;
class Tile;
class Entity;
class Level;

struct Attack {
	int normal_damage;
	int magic_damage;
	int fire_damage;
};

class Object {
public:
	virtual void update(Level* level) = 0;

	// TODO: draw function

	virtual bool is_solid() = 0;
};

class Tile : public Object {
public:
	virtual void update(Level* level) = 0;

	// draw();

	virtual bool is_solid() = 0;

	virtual void interact(Entity* ent) = 0;
};

class Entity : public Object {
protected:
	int x, y;

public:
	virtual void update(Level* level) = 0;

	//draw();

	virtual bool is_solid() = 0;

	virtual void hurt(Attack attack) = 0;

	virtual bool is_alive() = 0;

	int get_x();

	int get_y();
};

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

#endif
