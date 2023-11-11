// menu.hpp
#ifndef CURSED_MENU_HPP_
#define CURSED_MENU_HPP_
#include "libtcod.hpp"
#include <string>
#include <vector>

class Option_Item {
private:
	const std::string name;

public:
	Option_Item(std::string name);

	const std::string& get_name();

	virtual int get_value() = 0;

	virtual void update() = 0;

	virtual void draw(tcod::Console& con, int x , int y) = 0;
};

class Option_Menu {
private:
	size_t selected;
	std::vector<Option_Item*> items;

public:
	void update();

	void draw(tcod::Console& con);
};

#endif
