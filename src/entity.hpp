// entity.hpp
#ifndef CURSED_ENTITY_HPP_
#define CURSED_ENTITY_HPP_
#include "ai.hpp"
#include "item.hpp"
#include "world.hpp"

struct Attack {
	int normal_damage;
	int magic_damage;
	int fire_damage;
};

enum class ENTITY_ACTION {
	WANDER,
	ATTACK_PLAYER
};

struct Action {
	ENTITY_ACTION intent;
	int actions_needed;
};

class Entity : public Object {
protected:
	int x, y;

public:
	Entity(int x, int y);

	bool is_transparent();

	virtual bool is_alive() = 0;

	virtual void update(Level& level, int actions) = 0;

	virtual void draw(tcod::Console& con) = 0;

	int get_x();

	int get_y();
};

class Living_Entity : public Entity {
	friend class AI;

protected:
	int health, max_health;

	Item_List inventory;
	std::vector<IUID> equipped_uids;

	Action act;

	int last_player_x, last_player_y;
	bool seen_player;

	int move_actions();

	bool move(Level& level, int x, int y);

	void look_for_player(Level& level);

public:
	Living_Entity(int x, int y, int max_health);

	bool is_solid();

	bool is_alive();

	void update(Level& level, int actions);

	void interact(Living_Entity* ent);

	virtual void hurt(Attack attack);

	void give_item(Item* item);
};

class Item_Entity : public Entity {
private:
	Item* item_ref;
	bool picked_up;

public:
	Item_Entity(int x, int y, Item* item_ref);

	~Item_Entity();

	void interact(Living_Entity* ent);

	bool is_solid();

	bool is_alive();

	void update(Level&, int);

	void draw(tcod::Console& con);

	Item* get_item();
};

class Worm_Entity : public Living_Entity {
public:
	Worm_Entity(int x, int y);

	void draw(tcod::Console& con);
};

class Goblin_Entity : public Living_Entity {
public:
	Goblin_Entity(int x, int y);

	void update(Level& level, int actions);

	void draw(tcod::Console& con);
};

#endif
