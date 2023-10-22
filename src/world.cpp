// world.cpp, holds the state of the level and all its entities
#include "world.hpp"

#include "libtcod.hpp"
#include <optional>
#include <vector>

#include "item.hpp"
#include "tile.hpp"

// class Entity

int Entity::get_x() {
	return x;
}

int Entity::get_y() {
	return y;
}

// class Living_Entity

void Living_Entity::move(Level& level, int new_x, int new_y) {
	bool can_move = false;
	if (level.can_walk(new_x, new_y)) {
		can_move = true;
	}

	Tile* tile = level.get_tile(new_x, new_y);
	if (tile) {
		tile->interact(this);
	}

	std::vector<Entity*> entities = level.entities_at(new_x, new_y);
	for (int i = 0; i < entities.size(); ++i) {
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
}

void Living_Entity::update(Level& level) {
	// TODO: trigger enemy AI from here
}

void Living_Entity::interact(Living_Entity* ent) {
	// TODO: Calculate attacking entity's damage
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

// class Level

Level::Level(int width, int height) {
	this->width = width;
	this->height = height;
	tiles.resize(width * height);
	for (int i = 0; i < width * height; ++i) {
		tiles[i] = new Const_Tile('.', COLOR_GREY, COLOR_BLANK, false);
	}
}

void Level::update() {
	for (int i = 0; i < width * height; ++i) {
		tiles[i]->update(*this);
	}

	for (int i = 0; i < entities.size(); ++i) {
		entities[i]->update(*this);
	}
}

void Level::draw(tcod::Console& con) {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			tiles[y * width + x]->draw(con, x, y);
		}
	}

	for (int i = 0; i < entities.size(); ++i) {
		entities[i]->draw(con);
	}
}

bool Level::can_walk(int x, int y) {
	Tile* tile = get_tile(x, y);
	if (!tile) {
		return false;
	}

	if (tile->is_solid()) {
		return false;
	}

	auto ents = entities_at(x, y);
	for (int i = 0; i < ents.size(); ++i) {
		if (ents[i]->is_solid()) {
			return false;
		}
	}

	return true;
}

std::vector<Entity*> Level::entities_at(int x, int y) {
	std::vector<Entity*> ents = {};
	for (int i = 0; i < entities.size(); ++i) {
		Entity* ent = entities[i];
		if (ent->get_x() == x && ent->get_y() == y) {
			ents.push_back(ent);
		}
	}

	return ents;
}

void Level::add_entity(Entity* entity) {
	entities.push_back(entity);
}

Tile* Level::get_tile(int x, int y) {
	if (x < width && y < height && x >= 0 && y >= 0) {
		return tiles[y * width + x];
	}

	return nullptr;
}

void Level::set_tile(Tile* tile, int x, int y) {
	tiles[y * width + x] = tile;
}

int Level::get_width() {
	return width;
}

int Level::get_height() {
	return height;
}
