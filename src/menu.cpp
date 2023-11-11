// menu.cpp
#include "menu.hpp"

#include <string>

#include "keyboard.hpp"

// class Option_Item

Option_Item::Option_Item(std::string name) : name(name) {}

const std::string& Option_Item::get_name() {
	return name;
}

// class Option_Menu

void Option_Menu::update() {
	if (key_typed(SDL_SCANCODE_UP)) {
		selected--;
		if (selected >= items.size()) {
			selected = items.size() - 1;
		}
	}
	if (key_typed(SDL_SCANCODE_DOWN)) {
		selected++;
		if (selected >= items.size()) {
			selected = 0;
		}
	}
	items[selected]->update();
}