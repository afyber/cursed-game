// world.hpp
#ifndef CURSED_WORLD_HPP_
#define CURSED_WORLD_HPP_
#include <vector>
#include "libtcod.hpp"
#include "item.hpp"

class Object;
class Tile;
class Entity;
class Living_Entity;
class Level;

struct Attack {
	int normal_damage;
	int magic_damage;
	int fire_damage;
};

struct Resistances {
	double normal_resistance;
	double magic_resistance;
	double fire_resistance;
};

class Object {
public:
	virtual void update(Level* level) = 0;

	// TODO: draw function

	// make interact take a Living_Entity*
	virtual void interact(Living_Entity* ent) = 0;

	virtual bool is_solid() = 0;
};

class Tile : public Object {
	// TODO
};

class Entity : public Object {
protected:
	int x, y;

public:
	// TODO

	virtual void hurt(Attack attack) = 0;

	virtual bool is_alive() = 0;

	int get_x();

	int get_y();
};

class Living_Entity : public Entity {
protected:
	int health;
	int max_health;
	Resistances resistances;

	Item_List inventory;

	void move(Level* level, int x, int y);

public:
	Living_Entity(int x, int y, int max_health);

	void update(Level* level);

	void interact(Living_Entity* ent);

	bool is_solid();

	void hurt(Attack attack);

	bool is_alive();

	void give_item(Item* item);
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
