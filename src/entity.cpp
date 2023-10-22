// entity.cpp
#include "entity.hpp"

#include "ai.hpp"
#include "draw.hpp"
#include "item.hpp"
#include "tile.hpp"
#include "world.hpp"

// class Entity

int Entity::get_x() {
	return x;
}

int Entity::get_y() {
	return y;
}

// class Living_Entity

void Living_Entity::move(Level& level, int new_x, int new_y) {
	bool can_move = level.can_walk(new_x, new_y);

	Tile* tile = level.get_tile(new_x, new_y);
	if (tile) {
		tile->interact(this);
	}

	std::vector<Entity*> entities = level.entities_at(new_x, new_y);
	for (size_t i = 0; i < entities.size(); ++i) {
		entities[i]->interact(this);
	}

	if (can_move) {
		x = new_x;
		y = new_y;
	}
}

Living_Entity::Living_Entity(int x, int y, int max_health) {
	this->x = x;
	this->y = y;
	this->max_health = max_health;
	health = max_health;
	resistances = { 0, 0, 0 };
	ai = AI();
}

void Living_Entity::update(Level& level, bool turn) {
	if (turn) {
		ai.move_random(level, this);
	}
}

void Living_Entity::interact(Living_Entity* ent) {
	// TODO: Calculate attacking entity's damage
	(void)ent;
	this->hurt({ 1, 0, 0 });
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

void Living_Entity::give_item(Item* item) {
	inventory.add_item(item);
}

// class Item_Entity

Item_Entity::Item_Entity(int x, int y, Item* item_ref) {
	this->x = x;
	this->y = y;
	this->item_ref = item_ref;
}

void Item_Entity::update(Level&, bool) {}

void Item_Entity::draw(tcod::Console& con) {
	print_console_tile(con, { 'i', COLOR_WHITE, COLOR_BLANK }, x, y);
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

// class Worm_Entity

Worm_Entity::Worm_Entity(int x, int y) : Living_Entity(x, y, 1) {}

void Worm_Entity::draw(tcod::Console& con) {
	print_console_tile(con, { '~', { 1, 255, 200, 200 }, COLOR_BLANK }, x, y);
}
