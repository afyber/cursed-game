// menu.cpp
#include "menu.hpp"

#include "libtcod.hpp"
#include <stdexcept>
#include <vector>

#include "keyboard.hpp"

std::vector<Menu*> menu_stack;
Menu_Value return_value;
bool return_handled = true;

void menu_return(Menu_Value v) {
	if (!return_handled) {
		throw std::runtime_error("Menu system attempted to return before handling previous return");
	}
	return_handled = false;
	return_value = v;
	menu_stack.erase(menu_stack.end() - 1);
}

bool menu_returned() {
	return !return_handled;
}

Menu_Value menu_recieve() {
	if (return_handled) {
		throw std::runtime_error("Menu system attempted to get return value before value was returned");
	}
	return_handled = true;
	return return_value;
}

void menu_push(Menu* m) {
	menu_stack.push_back(m);
}

bool menu_open() {
	return menu_stack.size() > 0;
}

void update_menus() {
	if (menu_stack.size() > 0) {
		menu_stack[menu_stack.size() - 1]->update();
	}
}

void draw_menus(tcod::Console& con) {
	for (int i = 0; i < menu_stack.size(); ++i) {
		menu_stack[menu_stack.size() - 1]->draw(con);
	}
}

Choice_Menu::Choice_Menu(const char* message) : message(message), lines(tcod::get_height_rect(14, message)), selected(true) {}

void Choice_Menu::update() {
	if (key_typed(SDL_SCANCODE_LEFT) || key_typed(SDL_SCANCODE_RIGHT)) {
		selected = selected ^ true;
	}
	if (key_pressed(SDL_SCANCODE_KP_ENTER)) {
		menu_return(Menu_Value{ selected });
	}
}

void Choice_Menu::draw(tcod::Console& con) {
	tcod::print_frame(con, { 32, 20 - lines, 16, 6 + lines }, "Choose", new TCOD_ColorRGB{ 200, 0, 0 }, new TCOD_ColorRGB{ 0, 0, 0 });
	tcod::print_rect(con, { 33, 21 - lines, 14, lines }, message, TCOD_ColorRGB{ 200, 0, 0 }, std::nullopt);
	tcod::print(con, { 35, 23 }, "Yes", TCOD_ColorRGB{ 255, 255, 255 }, selected ? std::optional(TCOD_ColorRGB{ 200, 0, 0 }) : std::nullopt);
	tcod::print(con, { 43, 23 }, "No", TCOD_ColorRGB{ 255, 255, 255 }, !selected ? std::optional(TCOD_ColorRGB{ 200, 0, 0 }) : std::nullopt);
}