// map.cpp
#include "map.hpp"

#include "entity.hpp"
#include "tile.hpp"
#include "random.hpp"
#include "world.hpp"

// class Map

Map::Map(int width, int height) : width(width), height(height) {
	tiles.resize((size_t)width * height);

	for (size_t i = 0; i < tiles.size(); ++i) {
		if (irandom(1, 4) == 1) {
			tiles[i] = { new Const_Tile('#', COLOR_GREY, COLOR_BLANK, true, false), true, false };
		}
		else {
			tiles[i] = { new Const_Tile('.', { 1, 99, 52, 2 }, COLOR_BLANK, false, true), true, false };
		}
	}
}

void Map::update(Level& level) {
	for (size_t i = 0; i < tiles.size(); ++i) {
		tiles[i].tile_ref->update(level);
	}
}

void Map::draw(tcod::Console& con) {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if (tiles[(size_t)y * width + x].visible) {
				tiles[(size_t)y * width + x].tile_ref->draw(con, x, y);
			}
		}
	}
}

void Map::interact(int x, int y, Living_Entity* ent) {
	if (x > 0 && x < width && y > 0 && y < height) {
		tiles[(size_t)y * width + x].tile_ref->interact(ent);
	}
}

bool Map::is_solid(int x, int y) {
	if (x > 0 && x < width && y > 0 && y < height) {
		return tiles[(size_t)y * width + x].tile_ref->is_solid();
	}

	return true;
}

bool Map::is_transparent(int x, int y) {
	if (x > 0 && x < width && y > 0 && y < height) {
		return tiles[(size_t)y * width + x].tile_ref->is_transparent();
	}

	return false;
}

bool Map::is_visible(int x, int y) {
	if (x > 0 && x < width && y > 0 && y < height) {
		return tiles[(size_t)y * width + x].visible;
	}

	return false;
}

bool Map::seen(int x, int y) {
	if (x > 0 && x < width && y > 0 && y < height) {
		return tiles[(size_t)y * width + x].seen;
	}

	return false;
}
