// entity.cpp
#include "entity.hpp"

#include "ai.hpp"
#include "draw.hpp"
#include "item.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "world.hpp"

// class Entity

Entity::Entity(int x, int y) : x(x), y(y) {}

bool Entity::is_transparent() {
	return true;
}

int Entity::get_x() {
	return x;
}

int Entity::get_y() {
	return y;
}

// class Living_Entity

int Living_Entity::move_actions() {
	return 120;
}

bool Living_Entity::move(Level& level, int new_x, int new_y) {
	if (x == new_x && y == new_y) {
		return true;
	}

	bool can_move = level.can_walk(new_x, new_y);

	level.interact(new_x, new_y, this);

	std::vector<Entity*> entities = level.entities_at(new_x, new_y);
	for (size_t i = 0; i < entities.size(); ++i) {
		entities[i]->interact(this);
	}

	if (can_move) {
		x = new_x;
		y = new_y;
	}

	return can_move;
}

void Living_Entity::look_for_player(Level& level) {
	if (level.get_map().is_visible(x, y)) {
		last_player_x = level.get_player()->get_x();
		last_player_y = level.get_player()->get_y();
		seen_player = true;
	}
}

Living_Entity::Living_Entity(int x, int y, int max_health) : Entity(x, y), health(max_health), max_health(max_health), act(Action{ ENTITY_ACTION::WANDER, move_actions() }), seen_player(false) {}

void Living_Entity::update(Level& level, int actions) {
	while (act.actions_needed < actions) {
		actions -= act.actions_needed;
		switch (act.intent) {
		case ENTITY_ACTION::WANDER:
			AI::move_random(level, this);
			act = Action{ ENTITY_ACTION::WANDER, move_actions() };
		}
	}
	act.actions_needed -= actions;
}

void Living_Entity::interact(Living_Entity* ent) {
	// TODO: Calculate attacking entity's damage
	(void)ent;
	this->hurt(Attack{ 1, 0, 0 });
}

bool Living_Entity::is_solid() {
	return true;
}

void Living_Entity::hurt(Attack attack) {
	health -= attack.normal_damage + attack.magic_damage + attack.fire_damage;
}

void Living_Entity::kill(Level& level) {
	for (int i = 0; i < inventory.size(); ++i) {
		level.add_entity(new Item_Entity(x, y, inventory.at(i)));
	}
}

bool Living_Entity::is_alive() {
	return health > 0;
}

void Living_Entity::give_item(Item* item) {
	inventory.add_item(item);
}

// class Item_Entity

Item_Entity::Item_Entity(int x, int y, Item* item_ref) : Entity(x, y), item_ref(item_ref), picked_up(false) {}

Item_Entity::~Item_Entity() {
	// This will only free the Item* if the Item_Entity is deleted in a level change, and not if it was picked up by an Entity
	if (!picked_up) {
		delete item_ref;
	}
}

void Item_Entity::update(Level&, int) {}

void Item_Entity::draw(tcod::Console& con) {
	if (!picked_up) {
		print_console_tile(con, Console_Tile{ 'i', COLOR_WHITE, COLOR_BLANK }, x, y);
	}
}

bool Item_Entity::is_solid() {
	return false;
}

void Item_Entity::interact(Living_Entity* ent) {
	if (!picked_up) {
		ent->give_item(item_ref);
		picked_up = true;
	}
}

bool Item_Entity::is_alive() {
	return !picked_up;
}

void Item_Entity::kill(Level&) {}

Item* Item_Entity::get_item() {
	return item_ref;
}

// class Worm_Entity

Worm_Entity::Worm_Entity(int x, int y) : Living_Entity(x, y, 1) {}

void Worm_Entity::draw(tcod::Console& con) {
	print_console_tile(con, Console_Tile{ '~', Color{ 1, 255, 200, 200 }, COLOR_BLANK }, x, y);
}

// class Goblin_Entity

Goblin_Entity::Goblin_Entity(int x, int y) : Living_Entity(x, y, 5) {}

void Goblin_Entity::update(Level& level, int actions) {
	while (act.actions_needed < actions) {
		actions -= act.actions_needed;

		// take an action
		switch (act.intent) {
		case ENTITY_ACTION::WANDER:
			AI::move_random(level, this);
			break;
		case ENTITY_ACTION::ATTACK_PLAYER:
			AI::move_towards_player(level, this);
			break;
		}

		// decide what the next action should be
		look_for_player(level);
		if (seen_player) {
			act = Action{ ENTITY_ACTION::ATTACK_PLAYER, move_actions() };
		}
		else {
			act = Action{ ENTITY_ACTION::WANDER, move_actions() };
		}
	}
	act.actions_needed -= actions;
}

void Goblin_Entity::draw(tcod::Console& con) {
	print_console_tile(con, Console_Tile{ 'g', Color{ 1, 10, 100, 0 }, COLOR_BLANK }, x, y);
}
