// map.cpp
#include "map.hpp"

#include "libtcod.hpp"
#include <vector>

#include "draw.hpp"
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
				print_console_tile(con, tiles[(size_t)y * width + x].tile_ref->get_tile(), x, y);
			}
			else if (tiles[(size_t)y * width + x].seen) {
				print_console_tile(con, tiles[(size_t)y * width + x].seen_tile, x, y);
			}
		}
	}
}

void Map::interact(int x, int y, Living_Entity* ent) {
	if (x > 0 && x < width && y > 0 && y < height) {
		tiles[(size_t)y * width + x].tile_ref->interact(ent);
	}
}

void Map::calculate_visibility(std::vector<Entity*> const& entities, int player_x, int player_y) {
	TCODMap tmp_map(width, height);

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Tile* tile = tiles[(size_t)y * width + x].tile_ref;
			tmp_map.setProperties(x, y, tile->is_transparent(), !tile->is_solid());
		}
	}

	for (size_t i = 0; i < entities.size(); ++i) {
		Tile* tile = tiles[(size_t)entities[i]->get_y() * width + entities[i]->get_x()].tile_ref;
		if (entities[i]->is_solid()) {
			tmp_map.setProperties(entities[i]->get_x(), entities[i]->get_y(), tmp_map.isTransparent(entities[i]->get_x(), entities[i]->get_y()), false);
		}
		if (!entities[i]->is_transparent()) {
			tmp_map.setProperties(entities[i]->get_x(), entities[i]->get_y(), false, tmp_map.isWalkable(entities[i]->get_x(), entities[i]->get_y()));
		}
	}

	tmp_map.computeFov(player_x, player_y, FOV_RESTRICTIVE);

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			bool visible = tmp_map.isInFov(x, y);
			tiles[(size_t)y * width + x].visible = visible;
			if (visible) {
				tiles[(size_t)y * width + x].seen = true;
				Console_Tile t = tiles[(size_t)y * width + x].tile_ref->get_tile();
				t.fg = { 1, 65, 65, 65 };
				t.bg = { 1, 0, 0, 0 };
				tiles[(size_t)y * width + x].seen_tile = t;
			}
		}
	}
}

bool Map::is_solid(int x, int y) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return tiles[(size_t)y * width + x].tile_ref->is_solid();
	}

	return true;
}

bool Map::is_transparent(int x, int y) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return tiles[(size_t)y * width + x].tile_ref->is_transparent();
	}

	return false;
}

bool Map::is_visible(int x, int y) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return tiles[(size_t)y * width + x].visible;
	}

	return false;
}

bool Map::seen(int x, int y) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return tiles[(size_t)y * width + x].seen;
	}

	return false;
}
