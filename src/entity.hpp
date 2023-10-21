// entity.hpp
#ifndef CURSED_ENTITY_HPP_
#define CURSED_ENTITY_HPP_
#include "item.hpp"
#include "world.hpp"

class Item_Entity : public Entity {
private:
	Item* item_ref;

public:
	Item_Entity(int x, int y, Item* item_ref);

	void update(Level& level);

	void draw(tcod::Console& con);

	void interact(Living_Entity* ent);

	bool is_solid();

	bool is_alive();

	Item* get_item();
};

#endif
