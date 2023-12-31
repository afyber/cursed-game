// world.hpp
#ifndef CURSED_WORLD_HPP_
#define CURSED_WORLD_HPP_
#include "libtcod.hpp"
#include <vector>

#include "map.hpp"

#include "definitions.hpp"

class Object {
public:
	virtual void interact(Living_Entity* ent) = 0;

	virtual bool is_solid() = 0;

	virtual bool is_transparent() = 0;
};

class Level {
private:
	int width, height;
	Map map;

	std::vector<Entity*> entities;
	Player* player;

public:
	Level(int width, int height, Player* player);

	~Level();

	void update();

	void draw(tcod::Console& con);

	void interact(int x, int y, Living_Entity* ent);

	bool can_walk(int x, int y);

	std::vector<Entity*> entities_at(int x, int y);

	void add_entity(Entity* entity);

	bool remove_entity(Entity* entity);

	Player* get_player();

	Map& get_map();

	int get_width();

	int get_height();
};

#endif
