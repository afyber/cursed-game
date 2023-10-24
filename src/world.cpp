// world.cpp, holds the state of the level and all its entities
#include "world.hpp"

#include "libtcod.hpp"
#include <optional>
#include <vector>

#include "draw.hpp"
#include "entity.hpp"
#include "item.hpp"
#include "player.hpp"
#include "random.hpp"
#include "tile.hpp"

// class Level

void Level::calculate_visibility(int origin_x, int origin_y) {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Tile* tile = tiles[(size_t)y * width + x];
			visibility_map.setProperties(x, y, tile->is_transparent(), !tile->is_solid());
		}
	}

	for (size_t i = 0; i < entities.size(); ++i) {
		Entity* ent = entities[i];
		bool tile_walkable = visibility_map.isWalkable(ent->get_x(), ent->get_y());
		bool tile_transparent = visibility_map.isWalkable(ent->get_x(), ent->get_y());
		if (!ent->is_transparent()) {
			visibility_map.setProperties(ent->get_x(), ent->get_y(), false, tile_walkable);
		}
		if (ent->is_solid()) {
			visibility_map.setProperties(ent->get_x(), ent->get_y(), tile_transparent, false);
		}
	}

	visibility_map.computeFov(origin_x, origin_y, FOV_RESTRICTIVE);
}

Level::Level(int width, int height, Player* player) : visibility_map(width, height) {
	this->width = width;
	this->height = height;
	tiles.resize((size_t)width * height);
	for (size_t i = 0; i < (size_t)width * height; ++i) {
		if (irandom(1, 4) == 1) {
			tiles[i] = new Const_Tile('#', COLOR_GREY, COLOR_BLANK, true, false);
		}
		else {
			tiles[i] = new Const_Tile('.', { 1, 99, 52, 2 }, COLOR_BLANK, false, true);
		}
	}
	this->player = player;
}

void Level::update() {
	for (size_t i = 0; i < (size_t)width * height; ++i) {
		tiles[i]->update(*this);
	}

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

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if (visibility_map.isInFov(x, y)) {
				tiles[(size_t)y * width + x]->draw(con, x, y);
			}
		}
	}

	for (size_t i = 0; i < entities.size(); ++i) {
		Entity* ent = entities[i];
		if (visibility_map.isInFov(ent->get_x(), ent->get_y())) {
			ent->draw(con);
		}
	}

	player->draw(con);
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
	std::vector<Entity*> ents = {};
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

Tile* Level::get_tile(int x, int y) {
	if (x < width && y < height && x >= 0 && y >= 0) {
		return tiles[(size_t)y * width + x];
	}

	return nullptr;
}

void Level::set_tile(Tile* tile, int x, int y) {
	tiles[(size_t)y * width + x] = tile;
}

int Level::get_width() {
	return width;
}

int Level::get_height() {
	return height;
}
