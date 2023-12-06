// world.cpp, holds the state of the level and all its entities
#include "world.hpp"

#include "libtcod.hpp"
#include <optional>
#include <vector>

#include "draw.hpp"
#include "entity.hpp"
#include "item.hpp"
#include "map.hpp"
#include "player.hpp"
#include "random.hpp"
#include "tile.hpp"

// class Level

Level::Level(int width, int height, Player* player) : width(width), height(height), map(width, height), player(player) {
	map.calculate_visibility(entities, player->get_x(), player->get_y());
}

Level::~Level() {
	for (Entity* p : entities) {
		delete p;
	}
}

void Level::update() {
	map.update(*this);

	int actions = player->update(*this);

	if (actions > 0) {
		map.calculate_visibility(entities, player->get_x(), player->get_y());
	}

	for (size_t i = 0; i < entities.size(); ++i) {
		if (entities[i]->is_alive()) {
			entities[i]->update(*this, actions);
		}
		else {
			entities[i]->kill(*this);
			delete entities[i];
			entities.erase(entities.begin() + i);
		}
	}

	if (!player->is_alive()) {
		// TODO: gameover code
	}
}

void Level::draw(tcod::Console& con) {
	map.draw(con);

	for (size_t i = 0; i < entities.size(); ++i) {
		Entity* ent = entities[i];
		if (map.is_visible(ent->get_x(), ent->get_y())) {
			ent->draw(con);
		}
	}

	player->draw(con);
}

void Level::interact(int x, int y, Living_Entity* ent) {
	map.interact(x, y, ent);
}

bool Level::can_walk(int x, int y) {
	if (map.is_solid(x, y)) {
		return false;
	}

	auto ents = entities_at(x, y);
	for (size_t i = 0; i < ents.size(); ++i) {
		if (ents[i]->is_solid()) {
			return false;
		}
	}

	if (player->get_x() == x && player->get_y() == y) {
		return false;
	}

	return true;
}

std::vector<Entity*> Level::entities_at(int x, int y) {
	std::vector<Entity*> ents;
	for (size_t i = 0; i < entities.size(); ++i) {
		Entity* ent = entities[i];
		if (ent->get_x() == x && ent->get_y() == y) {
			ents.push_back(ent);
		}
	}

	if (player->get_x() == x && player->get_y() == y) {
		ents.push_back(player);
	}

	return ents;
}

void Level::add_entity(Entity* entity) {
	entities.push_back(entity);
}

bool Level::remove_entity(Entity* entity) {
	for (size_t i = 0; i < entities.size(); ++i) {
		if (entities[i] == entity) {
			entities.erase(entities.begin() + i);
			return true;
		}
	}

	return false;
}

Player* Level::get_player() {
	return player;
}

Map& Level::get_map() {
	return map;
}

int Level::get_width() {
	return width;
}

int Level::get_height() {
	return height;
}
