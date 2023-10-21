// entity.cpp
#include "entity.hpp"

#include "draw.hpp"
#include "item.hpp"
#include "world.hpp"

// class Item_Entity

Item_Entity::Item_Entity(int x, int y, Item* item_ref) {
	this->x = x;
	this->y = y;
	this->item_ref = item_ref;
}

void Item_Entity::update(Level& level) {}

void Item_Entity::draw(tcod::Console& con) {
	print_console_tile(con, Console_Tile{ 'i', Color{ 1, 255, 255, 255 }, Color{ 0, 0, 0, 0 } }, x, y);
}

bool Item_Entity::is_solid() {
	return false;
}

void Item_Entity::interact(Living_Entity* ent) {
	ent->give_item(item_ref);
}

bool Item_Entity::is_alive() {
	return true;
}

Item* Item_Entity::get_item() {
	return item_ref;
}
