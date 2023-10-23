// world.cpp, holds the state of the level and all its entities
#include "world.hpp"

#include "libtcod.hpp"
#include <optional>
#include <vector>

#include "entity.hpp"
#include "item.hpp"
#include "player.hpp"
#include "tile.hpp"

// class Level

Level::Level(int width, int height, Player* player) {
	this->width = width;
	this->height = height;
	tiles.resize((size_t)width * height);
	for (size_t i = 0; i < (size_t)width * height; ++i) {
		tiles[i] = new Const_Tile('.', COLOR_GREY, COLOR_BLANK, false);
	}
	this->player = player;
}

void Level::update() {
	for (size_t i = 0; i < (size_t)width * height; ++i) {
		tiles[i]->update(*this);
	}

	bool turn = player->update(*this);

	for (size_t i = 0; i < entities.size(); ++i) {
		entities[i]->update(*this, turn);
	}
}

void Level::draw(tcod::Console& con) {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			tiles[(size_t)y * width + x]->draw(con, x, y);
		}
	}

	for (size_t i = 0; i < entities.size(); ++i) {
		entities[i]->draw(con);
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
