// world.cpp, holds the state of the level and all its entities
#include "world.hpp"
#include <optional>

Level::Level(int width, int height) {
	this->width = width;
	this->height = height;
	for (int i = 0; i < width * height; ++i) {
		tiles.push_back(new Const_Tile('.', TCOD_ColorRGB{ 127, 127, 127 }, std::nullopt, true));
	}
}

void Level::update() {
	for (int i = 0; i < entities.size(); ++i) {
		entities[i]->update(this);
	}
}

void Level::draw(tcod::Console& con) {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			con.at({ x, y }) = tiles[y * width + x]->get_tile();
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

	if (!tile->is_passable()) {
		return false;
	}

	auto ents = entities_at(x, y);
	for (int i = 0; i < ents.size(); ++i) {
		if (!ents[i]->is_passable()) {
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

bool Entity::is_passable() {
	return true;
}

int Entity::get_x() {
	return x;
}

int Entity::get_y() {
	return y;
}