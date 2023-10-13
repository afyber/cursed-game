// world.cpp, holds the state of the level and all its entities
#include "world.hpp"
#include <optional>

Level::Level(int width, int height) {
	Level::width = width;
	Level::height = height;
	for (int i = 0; i < width * height; ++i) {
		Level::tiles.push_back(new Const_Tile('.', TCOD_ColorRGB{ 127, 127, 127 }, std::nullopt, true));
	}
}

Tile* Level::get_tile(int x, int y) {
	if (x < width && y < height && x >= 0 && y >= 0) {
		return Level::tiles[y * Level::width + x];
	}

	return 0;
}

int Level::get_width() {
	return Level::width;
}

int Level::get_height() {
	return Level::height;
}