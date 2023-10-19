// entity.cpp
#include "entity.hpp"

Item_Entity::Item_Entity(int x, int y, Item* item_ref) {
	this->x = x;
	this->y = y;
	this->item_ref = item_ref;
}

void Item_Entity::update(Level* level) {}

bool Item_Entity::is_solid() {
	return false;
}

void Item_Entity::hurt(Attack attack) {}

bool Item_Entity::is_alive() {
	return true;
}

Item* Item_Entity::get_item() {
	return item_ref;
}

void Living_Entity::move(Level* level, int x, int y) {
	if (level->can_walk(x, y)) {
		this->x = x;
		this->y = y;
	}

	Tile* tile = level->get_tile(x, y);
	if (tile) {
		tile->interact(this);
	}
}

Living_Entity::Living_Entity(int x, int y, int max_health) {
	this->x = x;
	this->y = y;
	this->max_health = max_health;
	health = max_health;
	resistances = Resistances{ 0, 0, 0 };
}

void Living_Entity::update(Level* level) {
	// TODO: trigger enemy AI from here
}

bool Living_Entity::is_solid() {
	return true;
}

void Living_Entity::hurt(Attack attack) {
	health -= (int)(attack.normal_damage * (1 - resistances.normal_resistance))
		+ (int)(attack.magic_damage * (1 - resistances.magic_resistance))
		+ (int)(attack.fire_damage * (1 - resistances.fire_resistance));
}

bool Living_Entity::is_alive() {
	return health > 0;
}
