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

void Level::calculate_visibility(int player_x, int player_y) {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			visibility_map.setProperties(x, y, map.is_transparent(x, y), !map.is_solid(x, y));
		}
	}

	for (size_t i = 0; i < entities.size(); ++i) {
		Entity* ent = entities[i];

		if (!ent->is_transparent()) {
			visibility_map.setProperties(ent->get_x(), ent->get_y(), false, visibility_map.isWalkable(ent->get_x(), ent->get_y()));
		}
		if (ent->is_solid()) {
			visibility_map.setProperties(ent->get_x(), ent->get_y(), visibility_map.isTransparent(ent->get_x(), ent->get_y()), false);
		}
	}

	visibility_map.computeFov(player_x, player_y, FOV_RESTRICTIVE);
}

Level::Level(int width, int height, Player* player) : width(width), height(height), player(player), visibility_map(width, height), map(width, height) {}

void Level::update() {
	map.update(*this);

	bool turn = player->update(*this);

	for (size_t i = 0; i < entities.size(); ++i) {
		if (entities[i]->is_alive()) {
			entities[i]->update(*this, turn);
		}
		else {
			remove_entity(entities[i]);
		}
	}

	if (!player->is_alive()) {
		// gameover code
	}
}

void Level::draw(tcod::Console& con) {
	calculate_visibility(player->get_x(), player->get_y());

	map.draw(con);

	for (size_t i = 0; i < entities.size(); ++i) {
		Entity* ent = entities[i];
		if (visibility_map.isInFov(ent->get_x(), ent->get_y())) {
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

int Level::get_width() {
	return width;
}

int Level::get_height() {
	return height;
}
