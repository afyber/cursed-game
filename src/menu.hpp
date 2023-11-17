// menu.hpp
#ifndef CURSED_MENU_HPP_
#define CURSED_MENU_HPP_
#include "libtcod.hpp"

class Menu {
public:
	virtual void update() = 0;

	virtual void draw(tcod::Console& con) = 0;
};

class List_Menu {
private:
	size_t selected;
	// std::vector<List_Item*> items;

public:
	void update();

	void draw(tcod::Console& con);
};

#endif
